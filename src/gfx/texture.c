#include "texture.h"
#include "array_list/array_list.h"
#include "coords/coords.h"
#include "core/config.h"
#include "core/types.h"
#include "screen/screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static array_list *texture_storage;

usize gfx_texture_load(texture_t t)
{
    usize id = gfx_texture_id_by_filename(t.filename);
    if (id != -1) {
        return id;
    }

    char *fp = core_config_get_asset_path(t.filename);

    t.texture = IMG_LoadTexture(screen_get_renderer(), fp);
    assert(t.texture != NULL);

    t.surface = IMG_Load(fp);
    assert(t.texture != NULL);

    t.cols = t.surface->w / t.cell_w;

    free(fp);
    return array_list_append(texture_storage, &t);
}

void gfx_texture_init()
{
    texture_storage = array_list_create(sizeof(texture_t), 128);

    gfx_texture_load((texture_t){.filename = "cropped/grass.png", .cell_w = 512, .cell_h = 256});
    gfx_texture_load((texture_t){.filename = "cropped/water.png", .cell_w = 512, .cell_h = 256});
    gfx_texture_load((texture_t){.filename = "cropped/beach.png", .cell_w = 512, .cell_h = 256});
    gfx_texture_load((texture_t){.filename = "cropped/watershore.png", .cell_w = 512, .cell_h = 256});
    gfx_texture_load((texture_t){.filename = "diamond_mask.png", .cell_w = 64, .cell_h = 32});
    gfx_texture_load((texture_t){.filename = "basic_tiles.png", .cell_w = 64, .cell_h = 32});
    gfx_texture_load((texture_t){.filename = "direction_tile.png", .cell_w = 64, .cell_h = 32});
    // gfx_texture_load((texture_t){.filename = "character/run.png", .cell_w = 64, .cell_h = 64});
    gfx_texture_load((texture_t){.filename = "character/idle.png", .cell_w = 64, .cell_h = 64});
    gfx_texture_load((texture_t){.filename = "trees.png", .cell_w = 64, .cell_h = 132});
}

texture_t *gfx_texture_get(usize id)
{
    return array_list_get(texture_storage, (size_t)id);
}

usize gfx_texture_id_by_filename(char *fname)
{
    texture_t *tex;
    for (usize i = 0; i < texture_storage->len; i++) {
        tex = gfx_texture_get(i);
        if (strcmp(tex->filename, fname) == 0)
            return i;
    }
    return -1;
}

texture_t *gfx_texture_by_filename(char *fname)
{
    return gfx_texture_get(gfx_texture_id_by_filename(fname));
}

SDL_Texture *gfx_texture_clip(texture_t *mask, texture_t *texture, i32 x, i32 y)
{
    SDL_Rect src_rect, dst_rect;
    vec2 pos;

    int cam_x = camera_x;
    int cam_y = camera_y;
    camera_x = 0;
    camera_y = 0;

    SDL_Texture *canvas = SDL_CreateTexture(screen_get_renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 512, 256);
    SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(screen_get_renderer(), canvas);

    // texture
    src_rect = (SDL_Rect){.w = 512, .h = 256, .x = 0, .y = 0};
    dst_rect = (SDL_Rect){.w = 512, .h = 256, .x = 0, .y = 0};
    SDL_RenderCopy(screen_get_renderer(), texture->texture, &src_rect, &dst_rect);

    // mask
    // FIXME: here we should not use zoom, and camera.
    // better just to copy-paste it here.
    pos = coords_tile_to_screen((vec2){.x = x, .y = y});
    src_rect = (SDL_Rect){.w = 64, .h = 32, .x = 0, .y = 0};
    dst_rect = (SDL_Rect){.w = 64, .h = 32, .x = pos.x + 512 * 0.5 - 32, .y = pos.y};
    SDL_SetTextureBlendMode(mask->texture, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(screen_get_renderer(), mask->texture, &src_rect, &dst_rect);

    // final cut
    src_rect = (SDL_Rect){.w = 64, .h = 32, .x = pos.x + 512 * 0.5 - 32, .y = pos.y};
    dst_rect = (SDL_Rect){.w = 64, .h = 32, .x = 0, .y = 0};

    SDL_Texture *result = SDL_CreateTexture(screen_get_renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 64, 32);
    SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(screen_get_renderer(), NULL);
    SDL_SetRenderTarget(screen_get_renderer(), result);
    SDL_RenderCopy(screen_get_renderer(), canvas, &src_rect, &dst_rect);
    SDL_SetRenderTarget(screen_get_renderer(), NULL);

    SDL_DestroyTexture(canvas);

    camera_x = cam_x;
    camera_y = cam_y;

    return result;
}
