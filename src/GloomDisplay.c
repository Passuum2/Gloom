#include "../include/Display.h"
#include "../include/Main.h"
#include "Character.h"
#include "Textures.h"

#define FOV (60.0 * M_PI / 180.0)

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,2,2,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1},
    {1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static double clamp(double nValue, double nMin, double nMax){
    if(nValue < nMin) return nMin;
    if (nValue > nMax) return nMax;
    return nValue;
}

int makeWorld(SDL_Window* window, SDL_Renderer* renderer, Player player){
    SDL_Surface *texWall = SDL_LoadBMP("Textures/WoodWall.bmp");
    if (!texWall) {forceStop();}
    SDL_Surface *fmtWall = SDL_ConvertSurfaceFormat(texWall, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(texWall);

    Uint32 *textureWall = (Uint32 *)fmtWall->pixels;
    int texWidthWall = fmtWall->w;
    int texHeightWall = fmtWall->h;

    SDL_Surface *texWall2 = SDL_LoadBMP("Textures/StoneFloor.bmp");
    if (!texWall2) {forceStop();}
    SDL_Surface *fmtWall2 = SDL_ConvertSurfaceFormat(texWall2, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(texWall2);

    Uint32 *textureWall2 = (Uint32 *)fmtWall2->pixels;
    int texWidthWall2 = fmtWall->w;
    int texHeightWall2 = fmtWall->h;

    SDL_Surface *texFloor = SDL_LoadBMP("Textures/StoneFloor.bmp");
    if (!texFloor) {forceStop();}
    SDL_Surface *fmtFloor = SDL_ConvertSurfaceFormat(texFloor, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(texFloor);

    Uint32 *textureFloor = (Uint32 *)fmtFloor->pixels;
    int texWidthFloor = fmtFloor->w;
    int texHeightFloor = fmtFloor->h;

    SDL_Surface *texCeiling = SDL_LoadBMP("Textures/ClothCeiling.bmp");
    if (!texCeiling) {forceStop();}
    SDL_Surface *fmtCeiling = SDL_ConvertSurfaceFormat(texCeiling, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(texCeiling);

    Uint32 *textureCeiling = (Uint32 *)fmtCeiling->pixels;

    SDL_Texture *screenTexture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    Uint32 *pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    player.x = 5.5;
    player.y = 17.5;
    player.angle = 0.0;
    double moveSpeed = 0.05 * log(player.character.Speed);
    if(moveSpeed <= 0) moveSpeed = 0.05;

    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) quit = 1;

        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        player = movePlayer(keys, player, moveSpeed, 0.05);

        double cosA = cos(player.angle);
        double sinA = sin(player.angle);

        for (int x = 0; x < SCREEN_WIDTH; x++) {
            double cameraX = 2.0 * x / SCREEN_WIDTH - 1.0;
            double rayDirX = cosA + sinA * cameraX;
            double rayDirY = sinA - cosA * cameraX;
            double invRayDirX = (rayDirX != 0) ? 1.0 / rayDirX : 1e30;
            double invRayDirY = (rayDirY != 0) ? 1.0 / rayDirY : 1e30;
            double deltaDistX = fabs(invRayDirX);
            double deltaDistY = fabs(invRayDirY);
            int mapX = (int)player.x;
            int mapY = (int)player.y;
            int stepX, stepY, side;
            double sideDistX, sideDistY;
            if (rayDirX < 0){
                stepX = -1;
                sideDistX = (player.x - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
            }
            if (rayDirY < 0){
                stepY = -1;
                sideDistY = (player.y - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
            }
            int hit = 0;
            while (!hit){
                if (sideDistX < sideDistY){
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (worldMap[mapY][mapX] > 0)
                    hit = 1;
            }
            double perpWallDist;
            if (side == 0)
                perpWallDist = (mapX - player.x + (1 - stepX) / 2) * invRayDirX;
            else
                perpWallDist = (mapY - player.y + (1 - stepY) / 2) * invRayDirY;
            int wallType = worldMap[mapY][mapX];
            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
            int drawStart = SCREEN_HEIGHT/2 - lineHeight/2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = SCREEN_HEIGHT/2 + lineHeight/2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT-1;
            double wallX;
            if (side == 0)
                wallX = player.y + perpWallDist * rayDirY;
            else
                wallX = player.x + perpWallDist * rayDirX;
            wallX -= floor(wallX);
            int texX = (int)(wallX * texWidthWall);
            if (side == 0 && rayDirX > 0)
                texX = texWidthWall - texX - 1;
            if (side == 1 && rayDirY < 0)
                texX = texWidthWall - texX - 1;
            Uint32 *wallTexture = (wallType == 2) ? textureWall2 : textureWall;
            for (int y = drawStart; y < drawEnd; y++){
                int d = y*256 - SCREEN_HEIGHT*128 + lineHeight*128;
                int texY = ((d * texHeightWall) / lineHeight) / 256;
                Uint32 color = wallTexture[texY * texWidthWall + texX];
                if (side)
                    color = (color >> 1) & 0x7F7F7F7F;

                pixels[y * SCREEN_WIDTH + x] = color;
            }
            double floorXWall, floorYWall;
            if (side == 0 && rayDirX > 0){
                floorXWall = mapX;
                floorYWall = mapY + wallX;
            }
            else if (side == 0 && rayDirX < 0){
                floorXWall = mapX + 1.0;
                floorYWall = mapY + wallX;
            }
            else if (side == 1 && rayDirY > 0){
                floorXWall = mapX + wallX;
                floorYWall = mapY;
            }
            else{
                floorXWall = mapX + wallX;
                floorYWall = mapY + 1.0;
            }

            double distWall = perpWallDist;

            for (int y = drawEnd + 1; y < SCREEN_HEIGHT; y++){
                double currentDist = SCREEN_HEIGHT / (2.0*y - SCREEN_HEIGHT);
                double weight = currentDist / distWall;
                double currentFloorX = weight * floorXWall + (1.0-weight)*player.x;
                double currentFloorY = weight * floorYWall + (1.0-weight)*player.y;
                int floorTexX = (int)(currentFloorX * texWidthFloor) % texWidthFloor;
                int floorTexY = (int)(currentFloorY * texHeightFloor) % texHeightFloor;
                if (floorTexX < 0) floorTexX += texWidthFloor;
                if (floorTexY < 0) floorTexY += texHeightFloor;

                Uint32 floorColor =
                    textureFloor[floorTexY * texWidthFloor + floorTexX];
                Uint32 ceilingColor =
                    textureCeiling[floorTexY * texWidthFloor + floorTexX];

                floorColor = (floorColor >> 1) & 0x7F7F7F7F;
                pixels[y * SCREEN_WIDTH + x] = floorColor;
                pixels[(SCREEN_HEIGHT - y) * SCREEN_WIDTH + x] = ceilingColor;
            }
        }

        SDL_UpdateTexture(screenTexture,NULL,pixels,SCREEN_WIDTH*sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,screenTexture,NULL,NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    free(pixels);
    SDL_FreeSurface(fmtWall);
    SDL_FreeSurface(fmtFloor);
    SDL_FreeSurface(fmtCeiling);
    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}