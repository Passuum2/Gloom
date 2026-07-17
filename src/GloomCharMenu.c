/* GloomCharMenu.c - Character Creation Screen for Gloom Game
 * Author: Myles Darity-Reese
 * Date: 12/18/25
 * 
 * Description: 
 *    
 * 
 * Functions:
 *    CharMenuIntil(): Initalizes Character Menu Struct
 *    
*/

#include "../include/Menu.h"      //Navigate(), CharacterMenu()
#include "../include/Audio.h"     //playBackground(), playSound()
#include "../include/Textures.h"  //texInit(), getPixels()
#include "../include/Character.h"
#include "../include/Letter.h"
#include "../include/Display.h"
#include "../lib/SDL2/include/SDL2/SDL.h"

int runningCM = 1;

void CharMenuIntil(Menu *charMenu){
    //CharMenuIntil(): Initalizes Character Menu Struct
    //Implementation: Sets number of items, items labels, and default select value
    //Note: Assumes space allocation to have 5 items
    charMenu->count = 5;
    charMenu->selected = 0;
    charMenu->items[0] = (MenuItem){"Warior", 0, 0};
    charMenu->items[1] = (MenuItem){"Mage", 0, 0};
    charMenu->items[2] = (MenuItem){"Hunter", 0, 0};
    charMenu->items[3] = (MenuItem){"Rouge", 0, 0};
    charMenu->items[4] = (MenuItem){"Goblin", 0, 0};
}

Player CharMenuButtons(int selected, SDL_Window *window, SDL_Renderer *renderer, char* name){
    //CharMenuButtons():
    //Implementation:
    Player player;
    player = createPlayer(selected);
    player.character.Name = name;
    runningCM = 0;
    return player;
}

void CharMenuDraw(SDL_Renderer* renderer, Menu* charMenu, int width, int height){
    //CharMenuDraw():
    //Implementation:
    for(int i = 0; i < charMenu->count; i++){
        charMenu->items[i].x = width/2;
        charMenu->items[i].y = 150 + i * 60;
        SDL_Rect rect = { charMenu->items[i].x - 100, charMenu->items[i].y, 200, 40 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        if (i == charMenu->selected)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawRect(renderer, &rect);
    }
}

void drawBox(SDL_Renderer* renderer, int x, int y, int width, int height){
    //drawBox():
    //Implementation:
    SDL_Rect rect = {x, y, height, width};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int thickness = 3;
    for(int i = 0; i < thickness; i++){
        SDL_Rect border = {
            x - i,
            y - i,
            height + (i * 2),
            width + (i * 2)
        }; 
        SDL_RenderDrawRect(renderer, &border);
    }
}

int CharacterMenu(SDL_Window *window, SDL_Renderer *renderer){
    Menu charMenu;
    Texture bg = texInit("Textures/StoneFloor.bmp");
    SDL_Event e;
    CharMenuIntil(&charMenu);
    Word warior = wordInit("warrior");
    Word mage = wordInit("mage");
    Word hunter = wordInit("hunter");
    Word theif = wordInit("theif");
    Word goblin = wordInit("goblin");
    Word type = wordInit("name");
    Player player;
    int winWidth, winHeight;
    int selected = -1;
   
    SDL_GetWindowSize(window, &winWidth, &winHeight);
    Uint32 *pixels = malloc(winWidth * winHeight * sizeof(Uint32));
    pixels = getPixels(bg, pixels, winWidth, winHeight);

    SDL_Texture *screenTexture = SDL_CreateTexture(renderer,
                                 SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING,
                                 winWidth,
                                 winHeight);
    int scale = 3;
    SDL_Texture *wariorWord = SDL_CreateTextureFromSurface(renderer, warior.surface);
    SDL_Texture *mageWord = SDL_CreateTextureFromSurface(renderer, mage.surface);
    SDL_Texture *hunterWord = SDL_CreateTextureFromSurface(renderer, hunter.surface);
    SDL_Texture *theifWord = SDL_CreateTextureFromSurface(renderer, theif.surface);
    SDL_Texture *goblinWord = SDL_CreateTextureFromSurface(renderer, goblin.surface);
    SDL_Texture *typeWord = SDL_CreateTextureFromSurface(renderer, type.surface);
    SDL_Texture *nameWord = NULL;

    SDL_Rect war = {
        winWidth/2 - (warior.width * scale)/2,
        winHeight/2 - ((150 - 1 * 60) - 10),
        warior.width * scale,
        warior.height * scale
    };
    SDL_Rect mag = {
        winWidth/2 - (mage.width * scale)/2,
        winHeight/2 - ((150 - 2 * 60) - 10),
        mage.width * scale,
        mage.height * scale
    };
    SDL_Rect hun = {
        winWidth/2 - (hunter.width * scale)/2,
        winHeight/2 - ((150 - 3 * 60) - 10),
        hunter.width * scale,
        hunter.height * scale
    };
    SDL_Rect thf = {
        winWidth/2 - (theif.width * scale)/2,
        winHeight/2 - ((150 - 4 * 60) - 10),
        theif.width * scale,
        theif.height * scale
    };
    SDL_Rect gob = {
        winWidth/2 - (goblin.width * scale)/2,
        winHeight/2 - ((150 - 5 * 60) - 10),
        goblin.width * scale,
        goblin.height * scale
    };
    SDL_Rect nam = {
        150,
        100,
        goblin.width * scale,
        goblin.height * scale
    };
    SDL_Rect typ = {
        42,
        100,
        type.width * scale,
        type.height * scale
    };

    char holder[16] = "";

    while(runningCM){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) runningCM = 0;
            selected = Navigate(&charMenu, &e);
            if(selected != -1) {player = CharMenuButtons(selected, window, renderer, holder);}
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE){
                size_t len = strlen(holder); 
                if (len > 0) holder[len - 1] = '\0';
                Word name = wordInit(holder);
                nam.w = name.width * scale;
                if (name.surface) nameWord = SDL_CreateTextureFromSurface(renderer, name.surface);
            }
            if(e.type == SDL_TEXTINPUT) {
                strncat(holder, e.text.text, sizeof(holder) - strlen(holder) - 1);
                Word name = wordInit(holder);
                nam.w = name.width * scale;
                if (name.surface) nameWord = SDL_CreateTextureFromSurface(renderer, name.surface);
            }
        }
        
        SDL_UpdateTexture(screenTexture, NULL, pixels, winWidth * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, screenTexture, NULL, NULL);

        CharMenuDraw(renderer, &charMenu, winWidth, winHeight);
        drawBox(renderer, 40, 98, type.height * scale + 5, 500);

        SDL_RenderCopy(renderer, wariorWord, NULL, &war);
        SDL_RenderCopy(renderer, mageWord, NULL, &mag);
        SDL_RenderCopy(renderer, hunterWord, NULL, &hun);
        SDL_RenderCopy(renderer, theifWord, NULL, &thf);
        SDL_RenderCopy(renderer, goblinWord, NULL, &gob);
        SDL_RenderCopy(renderer, nameWord, NULL, &nam);
        SDL_RenderCopy(renderer, typeWord, NULL, &typ);

        SDL_RenderPresent(renderer);
    }
    free(pixels);
    SDL_DestroyTexture(screenTexture);
    SDL_DestroyTexture(wariorWord);
    SDL_DestroyTexture(mageWord);
    SDL_DestroyTexture(hunterWord);
    SDL_DestroyTexture(theifWord);
    SDL_DestroyTexture(goblinWord);
    SDL_DestroyTexture(nameWord);
    SDL_DestroyTexture(typeWord);
    SDL_CloseAudioDevice(device);
    makeWorld(window, renderer, player);
    return 0;
}