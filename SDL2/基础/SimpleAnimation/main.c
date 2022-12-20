#include <SDL.h>

#define WIDTH 400
#define HEIGHT 300
/* 设定帧频 */
#define FRAMERATE 60

int x = 0;

void draw(SDL_Surface * screen, SDL_Window * win) {
    /* Background */
    SDL_Rect r={0, 0, WIDTH, HEIGHT}; //基础设置 x, y, w, h
    SDL_FillRect(screen, &r, 0xffffff); //设置填满窗口 Color:ARGB
    /* 红方块 */
    struct SDL_Rect redRect = {x, x, 100, 100};
    SDL_FillRect(screen, &redRect, 0xffff0000);
    // 更新窗口
    SDL_UpdateWindowSurface(win);
    x++;
}

/* 事件循环 */
void event_loop(SDL_Surface * screen, SDL_Window * win) {
    while (1) {
        /* 帧率：获取毫秒值 */
        long begin = SDL_GetTicks();
        /* 动画 */
        draw(screen,  win);

        SDL_Event event;
        /* 使用循环读取事件比if快，不用等 */
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                return;
            } 
        }

        /* 帧率：当前值 */
        long current = SDL_GetTicks();
        /* 现在每一帧花费的时间 */
        long cost = current - begin;
        /* 每帧应该的时间 */
        long frame = 1000/FRAMERATE;
        /* 计算该休眠的时间维持帧数 */
        long delay = frame - cost;
        /* 如果delay是负就不休眠维持帧数 */
        if (delay > 0) {
            SDL_Delay(delay);
        }
        /* 在系统资源足够的情况下能够保持一个足够的帧频，不够咱也没办法 */
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

    event_loop(screen, win);
    /* 释放窗口 */
    SDL_DestroyWindow(win);
    return 0;
}