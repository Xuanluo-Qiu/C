#include "Ball.h"
#include "Resource.h"
#include "Config.h"

// 创建小球，int x, y
Ball *Ball_Create(float x, float y, double rotateSpeed, float SpeedX, float SpeedY) {
    // 分配内存 内存大小->结构体大小
    Ball * b = malloc(sizeof(Ball));
    b->dest.x = x;
    b->dest.y = y;
    b->dest.w = 30;
    b->dest.h = 30;
    b->angle = 0;
    b->rotateSpeed = rotateSpeed;
    b->SpeedX = SpeedX;
    b->SpeedY = SpeedY;
    return b;
}

// 绘制小球, 渲染器renderer
void draw_Ball(Ball *self, SDL_Renderer *renderer) {
    self->angle += self->rotateSpeed;
    // xy向某个方向走
    self->dest.x += self->SpeedX;
    self->dest.y += self->SpeedY;
    // 控制边界
    // X
    // 超过边界并且值还是正的 SX * -1
    if (self->dest.x > WINDOW_WIDTH - self->dest.w && self->SpeedX>0) {
        self->SpeedX *= -1;
    }
    // 左边界 ..负数...*-1 变成正数
    if (self->dest.x<0 && self->SpeedX<0) {
        self->SpeedX *= -1;
    }
    // Y
    // 超过边界并且值还是正的 SY * -1
    if (self->dest.y > WINDOW_HEIGHT - self->dest.h && self->SpeedY>0) {
        self->SpeedY *= -1;
    }
    // 左边界 ..负数...*-1 变成正数
    if (self->dest.y<0 && self->SpeedY<0) {
        self->SpeedY *= -1;
    }


    // ..Ex -> ExF float
    SDL_RenderCopyExF(
        renderer,
        Restrict_GetBallTexture(),
        NULL,
        // 传入指针类型, 不是结构体的值
        &(self->dest),
        self->angle,
        NULL, SDL_FLIP_NONE
    );
}

// 清除小球 传入一个小球对象
void Ball_Destroy(Ball *ball) {
    free(ball);
}