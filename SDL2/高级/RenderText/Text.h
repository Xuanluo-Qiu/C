#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>
#include "DisplayObject.h"

// 字体 内容 大小
DisplayObject *TextCreate(char *fontFile, char *value, int ptsize, uint32_t color);

// 动态刷新
void TextSet(struct DisplayObject *textDisplayObject, char *value);

void TextDestroy(struct DisplayObject *self);
#endif