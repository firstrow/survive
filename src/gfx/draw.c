#include "draw.h"
#include "core/types.h"
#include "gfx/texture.h"
#include "gfx/animation.h"
#include "screen/screen.h"
#include "coords/coords.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

// draw on screen coords
void gfx_draw(texture_t *t, int sprite, vec2 screen_pos) {
    int src_x = (sprite % t->cols) * t->cell_w;
    int src_y = floor(sprite / t->cols) * t->cell_h;

    SDL_Rect src_rect = {.w=t->cell_w, .h=t->cell_h, .x=src_x, .y=src_y};
    SDL_Rect dst_rect = {.w=t->cell_w*SCALE_FACTOR, .h=t->cell_h*SCALE_FACTOR, .x=screen_pos.x, .y=screen_pos.y};
    SDL_RenderCopy(screen_get_renderer(), t->texture, &src_rect, &dst_rect);

    // draws rectangle around texture sprite
    /* SDL_Rect rect = {.x=screen_pos.x, .y=screen_pos.y, .w=dst_rect.w, .h=dst_rect.h}; */
    /* SDL_RenderDrawRect(screen_get_renderer(),  &rect); */
}

void gfx_draw_texture_on_map(texture_t *t, int sprite, vec2 map_pos) {
    vec2 pos = coords_tile_to_screen(map_pos);
    gfx_draw(t, sprite, pos);
}
