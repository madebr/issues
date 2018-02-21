#include <SDL.h>

#include <cstdio>

int do_sdl2(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        puts("Failed to initialize SDL2!\n");
        return 1;
    }

    SDL_Quit();

    return 0;
}
