/*
资源的统一管理
*/

#ifndef BALLS_RESOURCE_H
#define BALLS_RESOURCE_H

#include <SDL.h>
#include <SDL2/SDL_image.h>

// 创建
int Resource_Load(SDL_Renderer *renderer);
// 获取Texture
SDL_Texture *Restrict_GetBallTexture();
// 销毁
void Resource_UnLoad();

#endif