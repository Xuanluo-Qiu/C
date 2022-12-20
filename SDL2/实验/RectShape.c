#include "RectShape.h"

// 有检测

// 创建矩形框
RectShape *RectShape_Create(float x, float y, float w, float h, uint32_t color) {
    // 分配内存
    RectShape *self = malloc(sizeof(RectShape));
    self->color = color;
    self->dest.x = x;
    self->dest.y = y;
    self->dest.w = w;
    self->dest.h = h;
    // 默认不启用拖动属性
    self->_dragEnabled = 0;
    return self;
}

// 绘制
void RectShape_Draw(RectShape *self, SDL_Renderer *renderer) {
    // 提取颜色通道
    // 0xffff0000 ARGB
    SDL_SetRenderDrawColor(
        renderer,
        // RGBA
        // 提取红色通道值，右移xx位
        (self->color & 0x00ff0000) >> 16, // 红    r
        (self->color & 0x0000ff00) >> 8,  // 绿    g
        self->color & 0x000000ff,         // 蓝    b
        (self->color & 0xff000000) >> 24  // 透明  a
    );
    // &取地址
    SDL_RenderFillRectF(renderer, &(self->dest));
}

// 鼠标事件（拖动） .. SDL_Event是事件类型
SDL_bool RectShape_OnMouseEvent(RectShape *self, SDL_Event *event) {
    // // 检测碰撞(鼠标和红色块)
    SDL_Point currentMousePoint = {event->button.x, event->button.y};
    // 转换类型
    SDL_Rect destRect = {(int) self->dest.x, (int) self->dest.y, (int) self->dest.w, (int) self->dest.h};

    switch (event->type) {
        // 鼠标移动事件
        case SDL_MOUSEMOTION:
            // 点击时开始和鼠标一起拖动
            if (self->_dragEnabled == 1) {
                self->dest.x = self->_dragStartPoint.x + event->motion.x - self->_dragStartMousePoint.x;
                self->dest.y = self->_dragStartPoint.y + event->motion.y - self->_dragStartMousePoint.y;
                return SDL_TRUE;
            }
            break;
        // 鼠标点下事件
        case SDL_MOUSEBUTTONDOWN:
            if (SDL_PointInRect(&currentMousePoint, &destRect)) {
                // 当鼠标按下时，开始拖动
                self->_dragStartPoint.x = self->dest.x;
                self->_dragStartPoint.y = self->dest.y;
                self->_dragStartMousePoint.x = event->button.x;
                self->_dragStartMousePoint.y = event->button.y;
                self->_dragEnabled = 1;
                return SDL_TRUE;
            }
            break;
        // 鼠标弹起事件
        case SDL_MOUSEBUTTONUP:
            if (SDL_PointInRect(&currentMousePoint, &destRect)) {
                self->_dragEnabled = 0;
                return SDL_TRUE;
            }
            break;
    }
    return SDL_FALSE;
}

// 销毁
void RectShape_Destroy(RectShape *self) {
    free(self);
}
