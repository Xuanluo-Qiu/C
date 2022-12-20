#include "Resource.h"
#include "SDL2/SDL_image.h"

// 文件
#define BALL_FILE_NAME "ball.png"

// 图片
SDL_Texture *Ball_Texture;

// 创建
int Resource_Load(SDL_Renderer *renderer) {
    Ball_Texture = IMG_LoadTexture(renderer, BALL_FILE_NAME);
    if (Ball_Texture==NULL) {
        SDL_Log("Can not load texture, %s", IMG_GetError());
        return 1;
    }
    return 0;
}

// 获取Texture
SDL_Texture *Restrict_GetBallTexture() {
    return Ball_Texture;
}

// 销毁
void Resource_UnLoad() {
    SDL_DestroyTexture(Ball_Texture);
}