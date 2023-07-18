#define SDL_MAIN_HANDLED
#if defined(WITH_SDL2)
#include <SDL2/SDL.h>
#elif defined(WITH_SDL3)
#include <SDL3/SDL.h>
#else
#pragma error "No SDL"
#endif

static void log_locales(void)
{
    SDL_Locale *locales = SDL_GetPreferredLocales();
    if (locales == NULL) {
        SDL_Log("Couldn't determine locales: %s", SDL_GetError());
    } else {
        SDL_Locale *l;
        unsigned int total = 0;
        SDL_Log("Locales, in order of preference:");
        for (l = locales; l->language; l++) {
            const char *c = l->country;
            SDL_Log(" - %s%s%s", l->language, c ? "_" : "", c ? c : "");
            total++;
        }
        SDL_Log("%u locales seen.", total);
        SDL_free(locales);
    }
}

int main(int argc, char *argv[]) {
#if defined(WITH_SDL2)
    SDL_SetMainReady();
#endif
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_InitSubSystem failed (%s)", SDL_GetError());
        return 1;
    }
    log_locales();

    SDL_Quit();
    return 0;
}
