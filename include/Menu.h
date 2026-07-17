#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "../lib/SDL2/include/SDL2/SDL.h"

#define MAX_MENU_ITEMS 5  //Default number Menu items: 5

typedef struct {
    char *label;
    int x, y;
} MenuItem;

typedef struct {
    MenuItem items[MAX_MENU_ITEMS];
    int count;
    int selected;
} Menu;

int Navigate(Menu *menu, SDL_Event *e);                          //Navigate(): Handels keyboard input to move menu selection up/down
int menu(SDL_Window *window, SDL_Renderer *renderer);            //menu(): Runs menu loop and handels rendering and input
int CharacterMenu(SDL_Window *window, SDL_Renderer *renderer);
void drawBox(SDL_Renderer* renderer, int x, int y, int width, int height);

#endif