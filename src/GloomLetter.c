#include "../include/Letter.h"

Word wordInit(char* str) {
    Word oString = {0};
    size_t len = strlen(str);
    oString.count = len;
    oString.letters = malloc(sizeof(SDL_Surface*) * len);
    int totalWidth = 0;
    int maxHeight = 0;
    for(int i = 0; i < len; i++){
        char path[128];
        snprintf(path, sizeof(path), "Textures/Letters/%c.bmp", str[i]);
        SDL_Surface *letter = SDL_LoadBMP(path);
        if (!letter) {
            printf("Failed loading %s\n", path);
            forceStop();
        }
        SDL_Surface *format = SDL_ConvertSurfaceFormat(letter, SDL_PIXELFORMAT_ARGB8888, 0);
        SDL_FreeSurface(letter);
        oString.letters[i] = format;
        totalWidth += format->w;
        if (format->h > maxHeight)
            maxHeight = format->h;
    }
    oString.surface = SDL_CreateRGBSurfaceWithFormat(
        0,
        totalWidth,
        maxHeight,
        32,
        SDL_PIXELFORMAT_ARGB8888
    );
    if (!oString.surface) {forceStop();}
    int offsetX = 0;
    for(int i = 0; i < len; i++){
        SDL_Rect dest = { offsetX, 0, 0, 0 };
        SDL_BlitSurface(oString.letters[i], NULL, oString.surface, &dest);
        offsetX += oString.letters[i]->w;
    }
    oString.width = totalWidth;
    oString.height = maxHeight;
    return oString;
}