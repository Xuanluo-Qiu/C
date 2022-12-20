#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include <SDL.h>

#define WIDTH 600
#define HEIGHT 600
/* 设定帧频 */
#define FRAMERATE 60
// 文件
#define FILE_NAME "cat.bmp"

// 渲染器
SDL_Renderer * renderer; 
// window
SDL_Window * window;
// BMP图片转换
SDL_Texture * image_Texture;


void draw() {
    // 渲染背景为白色，使用渲染器
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
    SDL_RenderClear(renderer);

    // 获取图片宽高，不获取会让图片铺满屏幕(NULL)
    int w, h;
    SDL_QueryTexture(image_Texture, NULL, NULL, &w, &h);
    // 指定目标框（设置渲染宽高）
    //SDL_Rect destRect = {x, y, w, h};
    // ... ... 原框 目标框 NULL->全部区域
    // 设定原框为NULL，将h设为100将对图像进行拉伸，如果两个拉伸度一样可以实现放大缩小操作
    SDL_Rect destRect = {0, 100, w, 100}; // x, y, w, h
    SDL_RenderCopy(renderer, image_Texture, NULL, &destRect);

    // 设定原框为desRect，h，w设为100，原框为desRect，将会进行裁切
    SDL_Rect destRect_0 = {0, 0, 100, 100}; // x, y, w, h
    SDL_RenderCopy(renderer, image_Texture, &destRect_0, &destRect_0);

    // 旋转，翻转
    // SDL_RenderCopy, SDL_RenderCopyEx(能旋转), SDL_RenderCopyExF(浮点)
    // SDL_RenderCopyEx(... , 角度, 中心点（NULL就默认中心), 水平/垂直翻转)
    // SDL_FLIP_NONE                         : 不翻转
    // SDL_FLIP_VERTICAL                     : 垂直翻转
    // SDL_FLIP_HORIZONTAL                   : 水平翻转
    // SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL : 同时翻转
    SDL_Rect destRect_1 = {100, 0, 100, 100}; // x, y, w, h
    SDL_RenderCopyEx(renderer, image_Texture, NULL, &destRect_1, 45, NULL, SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);

    // 转圈动画
    // 动画效果 - 转圈圈
    static double angle = 0;
    // 调整速度/方向
    // +/-= int
    // angle++;
    angle += 2;
    SDL_Rect destRect_angle = {200, 0, 100, 100}; // x, y, w, h
    SDL_RenderCopyEx(renderer, image_Texture, NULL, &destRect_angle, angle, NULL, SDL_FLIP_NONE);

    // 设定可视区域(目标区域)
    struct SDL_Rect viewport = {10, 50, w, h};
    SDL_RenderSetViewport(renderer, &viewport);


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

    // 加载图片
    SDL_Surface * img_Surface = SDL_LoadBMP(FILE_NAME);
    // 转换类型
    image_Texture = SDL_CreateTextureFromSurface(renderer, img_Surface);
    // 释放Surface(转换完不需要原来的了)
    SDL_FreeSurface(img_Surface);

    event_loop();
    /* 释放Texture */
    SDL_DestroyTexture(image_Texture);
    /* 释放渲染器 */
    SDL_DestroyRenderer(renderer);
    /* 释放窗口 */
    SDL_DestroyWindow(window);
    return 0;
}
