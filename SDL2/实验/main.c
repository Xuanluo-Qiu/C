#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "RectShape.h"
#include "Resource.h"
#include "Ball.h"
#include "Config.h"

// 渲染器
SDL_Renderer *renderer; 
// window
SDL_Window *window;
// RectShape
RectShape *rect[RECTSHAPE_COUNT];
// Balls
Ball *ball[BALL_COUNT];

// 加载小球
void createBalls() {
    for (int i=0; i<BALL_COUNT; i++) {
        ball[i] = Ball_Create(
          i*40, i*20, (rand()%10)-5, 
          // 0~5浮点类型
          ((float)(rand()%1000))/1000*5,
          ((float)(rand()%1000))/1000*5 );
    }
}

// 释放小球
void destroyBalls() {
    for (int i=0; i<BALL_COUNT; i++) {
        Ball_Destroy(ball[i]);
    }
}


void draw() {
    // 渲染背景为白色，使用渲染器
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
    SDL_RenderClear(renderer);

    for (int i=0; i<RECTSHAPE_COUNT; i++) {
        RectShape_Draw(rect[i], renderer);
    }
    
    for (int i=0; i<BALL_COUNT; i++) {
        // 渲染
        draw_Ball(ball[i], renderer);
    }


    // 使其生效（放到屏幕上）
    SDL_RenderPresent(renderer);
}

/* 事件循环 */
void event_loop() {
    while (1) {
        /* 帧率：获取毫秒值 */
        long begin = SDL_GetTicks();
        /* 绘制 */
        draw();

        SDL_Event event;
        /* 使用循环读取事件比if快，不用等 */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // 鼠标移动事件
                case SDL_MOUSEMOTION:
                // 鼠标点下事件
                case SDL_MOUSEBUTTONDOWN:
                // 鼠标弹起事件
                case SDL_MOUSEBUTTONUP:
                    // 转移到函数内部处理事件
                    // 从后往前处理
                    for (int i=RECTSHAPE_COUNT - 1; i >= 0; --i) {
                        if(RectShape_OnMouseEvent(rect[i], &event)) {
                            // 跳出for
                            break;
                        }
                    }
                    break;
                case SDL_QUIT: return;
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
        "毕生所学",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,WINDOW_HEIGHT,
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
    
    // 加载资源
    if(Resource_Load(renderer)) {
        return 1;
    }
    
    // 创建小球
    createBalls();

    // 创建
    rect[0] = RectShape_Create(0, 0, 80, 60, 0xffff0000); // 红
    rect[1] = RectShape_Create(100, 0, 80, 60, 0xffffff00); // 黄
    rect[2] = RectShape_Create(200, 0, 80, 60, 0xff0000ff); // 蓝
    rect[3] = RectShape_Create(300, 0, 80, 60, 0xff00ff00); // 蓝

    event_loop();
    // 销毁
    /* 释放小球 */
    destroyBalls();

    for (int i=0; i<RECTSHAPE_COUNT; i++) {
        RectShape_Destroy(rect[i]);
    }
    /* 释放渲染器 */
    SDL_DestroyRenderer(renderer);
    /* 释放窗口 */
    SDL_DestroyWindow(window);
    return 0;
}