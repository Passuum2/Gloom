#ifndef LET_H
#define LET_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "../lib/SDL2/include/SDL2/SDL.h"

typedef struct {
    SDL_Surface *surface;
    SDL_Surface **letters;
    Uint32 *pixels;
    int width, height, count;
} Word;

void forceStop(void);
Word wordInit(char *str);

#endif