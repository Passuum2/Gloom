#include "../include/Audio.h"
#include "../lib/SDL2/include/SDL2/SDL.h"

#define MAX_CHANNELS 16

SDL_AudioDeviceID device = 0;
SDL_AudioSpec audioSpec;

static Channel channels[MAX_CHANNELS];
static Sound background = { NULL, 0 };

void audioCallback(void* userdata, Uint8* stream, int len) {
    SDL_memset(stream, 0, len);

    for (int i = 0; i < MAX_CHANNELS; i++) {
        Channel* c = &channels[i];
        if (!c->active) continue;

        Uint32 remaining = c->sound->length - c->position;
        Uint32 toCopy = remaining < (Uint32)len ? remaining : (Uint32)len;

        SDL_MixAudioFormat(
            stream,
            c->sound->buffer + c->position,
            audioSpec.format,
            toCopy,
            SDL_MIX_MAXVOLUME
        );

        c->position += toCopy;
        if (c->position >= c->sound->length)
            c->active = 0;
    }
}

static int initDevice(void) {
    if (device) return 1;

    SDL_zero(audioSpec);
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_S16SYS;
    audioSpec.channels = 2;
    audioSpec.samples = 4096;
    audioSpec.callback = audioCallback;

    device = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
    if (!device) {
        printf("Audio open failed: %s\n", SDL_GetError());
        return 0;
    }

    SDL_PauseAudioDevice(device, 0);
    return 1;
}

void playBackground(const char* filename) {
    if (!initDevice()) return;

    if (!background.buffer) {
        SDL_LoadWAV(filename, &audioSpec, &background.buffer, &background.length);
    }

    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (!channels[i].active) {
            channels[i].sound = &background;
            channels[i].position = 0;
            channels[i].active = 1;
            break;
        }
    }
}

void playSound(const char* filename) {
    static Sound soundCache[32];
    static char loaded[32][128];
    static int soundCount = 0;

    if (!initDevice()) return;

    Sound* s = NULL;

    /* Check cache */
    for (int i = 0; i < soundCount; i++) {
        if (strcmp(loaded[i], filename) == 0) {
            s = &soundCache[i];
            break;
        }
    }

    /* Load if not cached */
    if (!s && soundCount < 32) {
        s = &soundCache[soundCount];
        SDL_LoadWAV(filename, &audioSpec, &s->buffer, &s->length);
        strcpy(loaded[soundCount], filename);
        soundCount++;
    }

    if (!s) return;

    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (!channels[i].active) {
            channels[i].sound = s;
            channels[i].position = 0;
            channels[i].active = 1;
            break;
        }
    }
}