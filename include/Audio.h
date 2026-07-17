#ifndef AUDIO_H
#define AUDIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../lib/SDL2/include/SDL2/SDL.h"

typedef struct {
    Uint8* buffer;
    Uint32 length;
} Sound;

typedef struct {
    const Sound* sound;
    Uint32 position;
    int active;
} Channel;

extern SDL_AudioDeviceID device;
extern SDL_AudioSpec audioSpec;

void audioCallback(void* userdata, Uint8* stream, int len);
void playBackground(const char* filename);
void playSound(const char* filename);

#endif