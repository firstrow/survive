#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <stdbool.h>
#include "core/types.h"
#include <SDL2/SDL.h>

typedef struct {
    usize id;
    char* filename;
    i32 cell_w;
    i32 cell_h;
    i32 cols;

    SDL_Texture *texture;
    SDL_Surface *surface;
} texture_t;

void gfx_texture_init();
texture_t *gfx_texture_get(usize id);
SDL_Texture *gfx_texture_clip(texture_t *mask, texture_t *texture, i32 x, i32 y);
usize gfx_texture_id_by_filename(char *fname);
texture_t *gfx_texture_by_filename(char *fname);
usize gfx_texture_load(texture_t t);

#endif // TEXTURE_H_
