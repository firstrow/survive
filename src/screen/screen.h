#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>

#define scale_quality "linear"

#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 1200

void screen_init();
void screen_destroy();
void screen_clear();
void screen_present();
SDL_Renderer *screen_get_renderer();
SDL_Window *screen_get_window();

#endif // SCREEN_H_
