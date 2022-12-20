#include <SDL.h>
#include "Resource.h"
#include "Config.h"


// 渲染器
SDL_Renderer *renderer;
// window
SDL_Window *window;


void draw() {
  // 渲染背景为白色，使用渲染器
  SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
  SDL_RenderClear(renderer);

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

    // 事件循环
    SDL_Event event;
    /* 使用循环读取事件比if快，不用等 */
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return;
      }
    }

    /* 帧率：当前值 */
    long current = SDL_GetTicks();
    /* 现在每一帧花费的时间 */
    long cost = current - begin;
    /* 每帧应该的时间 */
    long frame = 1000 / FRAMERATE;
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
    "Balls",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH, WINDOW_HEIGHT, 
    SDL_WINDOW_SHOWN);

  if (window == NULL) {
    SDL_Log("Can not create window, %s", SDL_GetError());
    return 1;
  }

  // 创建渲染器
  // 窗口 渲染驱动(索引) 用什么渲染
  // SDL_RENDERER_ACCELERATED 硬件加速 GPU
  // SDL_RENDERER_SOFTWARE CPU渲染 (什么MC行为)
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("Can not create renderer, %s", SDL_GetError());
  }

  // 加载资源
  if(Resource_Load(renderer)) {
    return 1;
  }

  // 加载鼠标指针
  SDL_SetCursor(Resource_GetCursor());
  event_loop();

  /* 释放所有资源 */
  Resource_UnLoad();
  /* 释放渲染器 */
  SDL_DestroyRenderer(renderer);
  /* 释放窗口 */
  SDL_DestroyWindow(window);

  return 0;
}