#include "../include/Textures.h"

void forceStop(){
    fprintf(stderr, "SDL error: %s\n", SDL_GetError());
    printf("SDL2 Error"); 
    system("pause");
    SDL_Quit(); 
    exit(1);
}

Texture texInit(const char *path){
    Texture tex;
    SDL_Surface *menuBackground = SDL_LoadBMP(path);
    if (!menuBackground) forceStop();
    SDL_Surface *format = SDL_ConvertSurfaceFormat(menuBackground, SDL_PIXELFORMAT_ARGB8888, 0);
    if (!format) forceStop();
    SDL_FreeSurface(menuBackground);
    tex.surface = format;
    tex.pixels = (Uint32 *)format->pixels;
    tex.width = format -> w;
    tex.height = format -> h;
    return tex;
}

Uint32* getPixels(Texture tex, Uint32 *pixels,int winWidth, int winHeight){
    for(int x = 0; x < winWidth; x++){
        for (int y = 0; y < winHeight; y++) {
            int texX = (x * tex.width) / winWidth;
            int texY = (y * tex.height) / winHeight;

            Uint32 color = tex.pixels[texY * tex.width + texX];
            color = (color >> 1) & 0x7F7F7F7F;
            pixels[y * winWidth + x] = color;
        }
    }
    return pixels;
}