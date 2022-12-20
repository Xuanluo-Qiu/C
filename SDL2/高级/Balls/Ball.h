#ifndef BALLS_BALL_H
#define BALLS_BALL_H

#include <SDL.h>

// 小球结构体
typedef struct {
    // FRect -> float Rect
    SDL_FRect dest;        // 基础属性
    double angle;         // 旋转角度值
    double rotateSpeed;   // 旋转速度
    double SpeedX, SpeedY;// 移动
} Ball;

// 创建小球，int x, y 返回值是球的对象
Ball *Ball_Create(float x, float y, double rotateSpeed, float SpeedX, float SpeedY);

// 绘制小球, 渲染器renderer, self是当前对象
void draw_Ball(Ball *self, SDL_Renderer *renderer);

// 清除小球 传入一个小球对象
void Ball_Destroy(Ball *);

#endif