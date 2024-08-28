#include "screen/screen.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

static struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL;

void screen_init()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL.window = SDL_CreateWindow(
        "Survive",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    SDL.renderer = SDL_CreateRenderer(
        SDL.window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // SDL_SetWindowPosition(SDL.window, 1400, 100);
    /* SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality); */
}

void screen_clear()
{
    SDL_SetRenderDrawColor(SDL.renderer, 0, 0, 0, 0);
    SDL_RenderClear(SDL.renderer);
}

void screen_present()
{
    SDL_RenderPresent(SDL.renderer);
}

void screen_destroy()
{
    SDL_DestroyWindow(SDL.window);
    SDL_DestroyRenderer(SDL.renderer);
}

SDL_Renderer *screen_get_renderer()
{
    return SDL.renderer;
}

SDL_Window *screen_get_window()
{
    return SDL.window;
}
