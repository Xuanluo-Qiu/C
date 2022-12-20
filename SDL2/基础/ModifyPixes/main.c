#include <SDL.h>

#define WIDTH 400
#define HEIGHT 300

/* 事件循环 */
void event_loop() {
    while (1) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT) {
                break;
            } 
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Can not init video, %s", SDL_GetError());
        return 1;
    }

    SDL_Window * win = SDL_CreateWindow(
        "Draw",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (win==NULL) {
        SDL_Log("Can not create window, %s", SDL_GetError());
        return 1;
    }

    // 渲染
    SDL_Surface * screen = SDL_GetWindowSurface(win); // 找到窗口

    /* Background */
    SDL_Rect r={0, 0, WIDTH, HEIGHT}; //基础设置 x, y, w, h
    SDL_FillRect(screen, &r, 0xffffff); //设置填满窗口 Color:ARGB

    /* 红方块 */
    struct SDL_Rect redRect = {0, 0, 100, 100};
    SDL_FillRect(screen, &redRect, 0xffff0000);

    /* 
    //访问像素 
    screen->pixels // 指向像素
    */
    // 修改第一百个像素变成蓝色
    ((uint32_t*)(screen->pixels))[100] = 0xff0000ff;
    // 在方块中间显示一个像素点
    // w为400，会继续向下查找 401 402.。。。
    // w*50 w为50 +50 y也是50
    ((uint32_t*)(screen->pixels))[WIDTH*50+50] = 0xff0000ff;
    // 绘制线
    for (int i=0; i<100; i++) {
        ((uint32_t*)(screen->pixels))[WIDTH*50+50+i] = 0xff0000ff;
    }
    

    // 更新窗口
    SDL_UpdateWindowSurface(win);

    event_loop();
    /* 释放窗口 */
    SDL_DestroyWindow(win);
    return 0;
}