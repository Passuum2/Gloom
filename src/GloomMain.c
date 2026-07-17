/* main.c - Entry point for Gloom Game
 * Author: Myles Darity-Reese
 * Date: 12/7/25
 * 
 * Description: 
 *    Intializes SDL. Creates window and renderer and starts game loop.
 * 
 * Functions:
 *    main(): Creates window and renderer and starts game loop.
 *   *makeWindow(): Creates SDL2 Window.
*/

#include "../include/Menu.h"                  //menu()
#include "../lib/SDL2/include/SDL2/SDL.h"

#define SCREEN_WIDTH 640   //Default Width of Window:  640 pixels
#define SCREEN_HEIGHT 480  //Default Height of Window: 480 pixels

SDL_Window* makeWindow(SDL_Window *window){
    //makeWindow(): Creates SDL2 Window.
    //Implementation: Calls to SDL2 lib.
    window = SDL_CreateWindow("Gloom (Prototype)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    return window;
}

int main(int argc, char *argv[]){
    //main(): Creates window and renderer and starts game loop.
    //Implementation: Calls to SDL2 lib and intializes SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {printf("SDL_Init Error: %s\n", SDL_GetError()); return 1;}

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window *window = makeWindow(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    menu(window, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}