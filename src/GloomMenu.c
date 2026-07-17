/* GloomMenu.c - Start Screen for Gloom Game
 * Author: Myles Darity-Reese
 * Date: 12/18/25
 * 
 * Description: 
 *    Implements start menu for Gloom Game
 *    Handels Initalization, Rendering, keyboard events,
 *    and transitions to other game states
 * 
 * Functions:
 *    MenuInit(): Initalizes a Menu Structure
 *    Navigate(): Handels keyboard input to move menu selection up/down
 *    MenuDraw(): Renders menu items in the centre horizontally of screen
 *    MenuButtons(): Execute Return Keyboard Event associated with selected
 *    menu(): Runs menu loop and handels rendering and input
*/

#include "../include/Menu.h"      //Navigate(), menu(), CharacterMenu()
#include "../include/Audio.h"     //playBackground(), playSound()
#include "../include/Textures.h"  //texInit(), getPixels()
#include "../include/Letter.h"
#include "../lib/SDL2/include/SDL2/SDL.h"

int runningM = 1;

int Navigate(Menu *menu, SDL_Event *e) {
    //Navigate(): Handels keyboard input to move menu selection up/down
    //Implementation: Increments/Decrements menu.count and calls to Audio.h
    int iRet = -1;
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.scancode) {
            case SDL_SCANCODE_UP:
                playSound("Sound/menu_sound.wav");
                menu->selected--;
                if (menu->selected < 0)
                    menu->selected = menu->count - 1;
                break;

            case SDL_SCANCODE_DOWN:
                playSound("Sound/menu_sound.wav");
                menu->selected++;
                if (menu->selected >= menu->count)
                    menu->selected = 0;
                break;

            case SDL_SCANCODE_RETURN:
                playSound("Sound/beep.wav");
                iRet = menu->selected;
                break;
        }
    }
    return iRet;
}

void MenuInit(Menu *menu) {
    //MenuInit(): Initalizes a Menu Structure
    //Implementation: Sets number of items, items labels, and default select value
    //Note: Assumes space allocation to have 5 items
    menu->count = 5;
    menu->selected = 0;
    menu->items[0] = (MenuItem){ "Start",   0, 0};
    menu->items[1] = (MenuItem){ "Load",    0, 0};
    menu->items[2] = (MenuItem){ "Options", 0, 0};
    menu->items[3] = (MenuItem){ "Credits", 0, 0};
    menu->items[4] = (MenuItem){ "Exit",    0, 0};
}

void MenuDraw(SDL_Renderer *renderer, Menu *menu, int width, int height) {
    //MenuDraw(): Renders menu items in the centre horizontally of screen
    //Implementation: x = w/2 y = 150 + #item * 60
    for (int i = 0; i < menu->count; i++) {
        menu->items[i].x = width/2;
        menu->items[i].y = 150 + i * 60;
        SDL_Rect rect = { menu->items[i].x - 100, menu->items[i].y, 200, 40 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        if (i == menu->selected)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawRect(renderer, &rect);
    }
}

void MenuButtons(int selected, SDL_Window *window, SDL_Renderer *renderer){
    //MenuButtons(): Execute Return Keyboard Event associated with selected
    //Implementation: Free pixels when transitioning to CharacterMenu
    switch(selected) {
        case 0:
            //Start: Transition to Character Menu
            runningM = 0;
            break;
        case 1:
            //Load: TODO
            runningM = 0;
            break;
        case 2:
            //Options: TODO
            runningM = 0;
            break;
        case 3:
            //Credit: TODO
            runningM = 0;
            break;
        case 4:
            //Exit: Shut down SDL and terminate program
            runningM = 0;
            SDL_Quit();
            exit(0);
            break;
    }
}

int menu(SDL_Window *window, SDL_Renderer *renderer){
    Menu menu;
    Texture bg = texInit("Textures/WoodWall.bmp");
    SDL_Event e;
    MenuInit(&menu);
    playBackground("Sound/Majula.wav");
    Word start = wordInit("start");
    Word quit = wordInit("quit");

    int winWidth, winHeight;
    int selected = -1;
    int scale = 3;

    SDL_GetWindowSize(window, &winWidth, &winHeight);

    Uint32 *pixels = malloc(winWidth * winHeight * sizeof(Uint32));
    pixels = getPixels(bg, pixels, winWidth, winHeight);

    SDL_Texture *screenTexture = SDL_CreateTexture(renderer,
                                        SDL_PIXELFORMAT_ARGB8888,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        winWidth,
                                        winHeight);

    SDL_Texture *startWord = SDL_CreateTextureFromSurface(renderer, start.surface);
    SDL_Texture *quitWord = SDL_CreateTextureFromSurface(renderer, quit.surface);

    SDL_Rect srt = {
        winWidth/2 - (start.width * scale)/2,
        winHeight/2 - ((150 - 1 * 60) - 10),
        start.width * scale,
        start.height * scale
    };
    SDL_Rect qut = {
        winWidth/2 - (quit.width * scale)/2,
        winHeight/2 - ((150 - 5 * 60) - 10),
        quit.width * scale,
        quit.height * scale
    };

    while(runningM) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) runningM = 0;
            selected = Navigate(&menu, &e);
            if (selected != -1) MenuButtons(selected, window, renderer);
        }
        SDL_UpdateTexture(screenTexture, NULL, pixels, winWidth * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, screenTexture, NULL, NULL);

        MenuDraw(renderer, &menu, winWidth, winHeight);

        SDL_RenderCopy(renderer, startWord, NULL, &srt);
        SDL_RenderCopy(renderer, quitWord, NULL, &qut);

        SDL_RenderPresent(renderer);
    }
    //TODO: Fix CHARACTERMENUDRAW to happen only when start is selected
    free(pixels);
    SDL_DestroyTexture(screenTexture);
    SDL_DestroyTexture(startWord);
    SDL_DestroyTexture(quitWord);
    CharacterMenu(window, renderer);
    return 0;
}