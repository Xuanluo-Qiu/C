#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 648
#define HEIGHT 648
/* 设定帧频 */
#define FRAMERATE 60
/* 字体大小(文字高度) */
#define FONT_SIZE 32

/* 声明图片 */
struct SDL_Surface * img;
/* 声明字体 */
TTF_Font * font;

int x = 0;

void draw(SDL_Surface * screen, SDL_Window * win) {
    // 图片渲染
    /* 设定img矩形框 */
    SDL_Rect src = {0, 0, img->w-10, img->h};//x, y, w, h
    /* 让img在win显示（copy上去） */
    SDL_BlitSurface(img, &src, screen, &src);
    
    // 文字渲染
    /* 字体颜色 */
    SDL_Color color = {225, 225, 225, 255}; // RGBA
    /* 渲染文字 */
    SDL_Surface * text = TTF_RenderUTF8_Blended(font, "东雪莲我真的好喜欢你啊", color); //字体 内容 字体(前景)颜色
    /* 显示到主屏幕 */
    // 矩形框
    SDL_Rect text_src = {0, 0, text->w, text->h};
    // 渲染到
    SDL_BlitSurface(text, &text_src, screen, &text_src);

    // 更新主屏幕
    SDL_UpdateWindowSurface(win);
}

/* 事件循环 */
void event_loop(SDL_Surface * screen, SDL_Window * win) {
    while (1) {
        /* 帧率：获取毫秒值 */
        long begin = SDL_GetTicks();

        /* 渲染 */
        draw(screen, win);

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
    if (TTF_Init()) {
        SDL_Log("Can not init ttf, %s", TTF_GetError());
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Can not init video, %s", SDL_GetError());
        return 1;
    }

    SDL_Window * win = SDL_CreateWindow(
        "img",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (win==NULL) {
        SDL_Log("Can not create window, %s", SDL_GetError());
        return 1;
    }

    /* 加载图片 */
    img = IMG_Load("img_2.jpg");
    if (img==NULL) {
        SDL_Log("Can not load image, %s", SDL_GetError());
        return 1;
    }

    /* 打开字体 */
    font = TTF_OpenFont("SourceHanSansCN-Bold.otf", FONT_SIZE);
    if (font==NULL) {
        SDL_Log("Can not open font");
    }

    SDL_Surface * screen = SDL_GetWindowSurface(win); // 找到窗口

    event_loop(screen, win);

    /* 释放图片 */
    SDL_FreeSurface(img);
    /* 释放字体 */
    TTF_CloseFont(font);
    /* 释放窗口 */
    SDL_DestroyWindow(win);
    return 0;
}
