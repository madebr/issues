#include <SDL.h>

#include <iostream>

int do_sdl2(int argc, char **argv) {
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    std::cout << "We compiled against SDL version "
        << int(compiled.major) << "." << int(compiled.minor) << "." << int(compiled.patch) << "\n";
    std::cout << "But we are linking against SDL version "
        << int(compiled.major) << "." << int(compiled.minor) << "." << int(compiled.patch) << "\n";

    return 0;
}
