// 抽象矩形框
#ifndef MOUSEEVENT_RECTSHAPE_H
#define MOUSEEVENT_RECTSHAPE_H

#include <SDL.h>

typedef struct {
    SDL_FRect dest;
    uint32_t color;
    // _代表内部使用
    // 记录起始点
    SDL_FPoint _dragStartPoint;
    // 记录开始拖动时鼠标的位置 了解鼠标移动的距离
    SDL_FPoint _dragStartMousePoint;
    // 是否被点击(是否启用)
    int _dragEnabled;
} RectShape;

// 创建矩形框
RectShape *RectShape_Create(float x, float y, float w, float h, uint32_t color);

// 绘图
void RectShape_Draw(RectShape *self, SDL_Renderer *renderer);

// 鼠标事件 .. SDL_Event是事件类型
SDL_bool RectShape_OnMouseEvent(RectShape *self, SDL_Event *event);

// 销毁
void RectShape_Destroy(RectShape *self);

#endif