#include "SDL_render.h"
#include <SDL.h>

#define WIDTH 400
#define HEIGHT 300
/* 设定帧频 */
#define FRAMERATE 60

// 渲染器
SDL_Renderer * renderer; 
// window
SDL_Window * window;

void draw() {
    // 渲染背景为白色，使用渲染器
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
    SDL_RenderClear(renderer);


    // 线条
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
    SDL_RenderDrawLine(renderer, 12, 12, 200, 200);

    // 很多线条
    // 静态初始化
    // 点的位置
    SDL_Point points[] = {
        {50, 50},
        {200, 200},
        {300, 200}
    };
    // 渲染器 数据 几个点
    SDL_RenderDrawLines(renderer, points, 3);

    // 绘制红色方块
    SDL_Rect r = {0, 0, 100, 100};
    // 重新设定颜色
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // 绘制
    SDL_RenderFillRect(renderer, &r);

    // 改成漠视为混合模式 用于支持透明混合，改透明度
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Blue Rect 透明度 100
    SDL_Rect br = {50, 30, 100, 100};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderFillRect(renderer, &br);


    // 使其生效（放到屏幕上）
    SDL_RenderPresent(renderer);
}

/* 事件循环 */
void event_loop() {
    while (1) {
        /* 帧率：获取毫秒值 */
        long begin = SDL_GetTicks();
        /* 动画 */
        draw();

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

    window = SDL_CreateWindow(
        "Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window==NULL) {
        SDL_Log("Can not create window, %s", SDL_GetError());
        return 1;
    }

    // 创建渲染器
    // 窗口 渲染驱动(索引) 用什么渲染
    // SDL_RENDERER_ACCELERATED 硬件加速 GPU
    // SDL_RENDERER_SOFTWARE CPU渲染 (什么MC行为)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer==NULL) {
        SDL_Log("Can not create renderer, %s", SDL_GetError());
    }

    event_loop();
    /* 释放渲染器 */
    SDL_DestroyRenderer(renderer);
    /* 释放窗口 */
    SDL_DestroyWindow(window);
    return 0;
}