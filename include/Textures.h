#ifndef TEX_H
#define TEX_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../lib/SDL2/include/SDL2/SDL.h"

typedef struct {
    SDL_Surface *surface;
    Uint32 *pixels;
    int width, height;
} Texture;

void forceStop(void);
Texture texInit(const char *path);
Uint32* getPixels(Texture tex, Uint32 *pixels, int winWidth, int winHeight);

#endif