#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "Character.h"
#include "../lib/SDL2/include/SDL2/SDL.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
int worldMap[MAP_HEIGHT][MAP_WIDTH];

static double clamp(double nValue, double nMin, double nMax);
int makeWorld(SDL_Window *window, SDL_Renderer *renderer, Player player);

#endif