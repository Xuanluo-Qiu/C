#include "Resource.h"

// 资源
SDL_Surface *cursorSurface;
// 鼠标指针
SDL_Cursor *cursor;

// 创建
int Resource_Load(SDL_Renderer *renderer) {
    cursorSurface = IMG_Load("cursor.png");
    if (cursorSurface==NULL) {
        SDL_Log("Can not load cursor, %s", IMG_GetError());
        return 1;
    }
    // 鼠标资源和初始位置加载
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    return 0;
}

// 获取
SDL_Surface *Restrict_GetCursorSurface() {
    return cursorSurface;
}


// 获取 - 指针
SDL_Cursor *Resource_GetCursor() {
    return cursor;
}



// 销毁
void Resource_UnLoad() {
    SDL_FreeCursor(cursor);
    SDL_FreeSurface(cursorSurface);
}