#include "ui.h"
#include "screen/screen.h"
#include "core/config.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font *font = NULL;
int font_size = 16;

SDL_Color UI_COLOR_WHITE = {255, 255, 255};
SDL_Color UI_COLOR_BLACK = {0, 0, 0};

void ui_init() {
    TTF_Init();

    font = TTF_OpenFont(core_config_get_asset_path("ttf/iosevka.ttf"), font_size);
    if (font == NULL) {
        SDL_LogError(0, "failed to load font");
        abort();
    }
}

void ui_draw_text(int x, int y, char *text, int size) {
    TTF_SetFontSize(font, size);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    SDL_Surface* surface_text = TTF_RenderText_Solid(font, text, UI_COLOR_WHITE);
    SDL_Texture* message = SDL_CreateTextureFromSurface(screen_get_renderer(), surface_text);
    if (message == NULL) {
        SDL_LogError(0, "failed to allocate mem for ui_draw_message");
        abort();
    }

    SDL_Rect message_rect = (SDL_Rect){.x = x, .y = y, .w = surface_text->w, .h = surface_text->h};
    SDL_RenderCopy(screen_get_renderer(), message, NULL, &message_rect);

    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(message);
    TTF_SetFontSize(font, font_size);
}
