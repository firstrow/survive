#include "game.h"
#include "ai/follower.h"
#include "coords/coords.h"
#include "core/direction.h"
#include "core/types.h"
#include "entity/entity.h"
#include "entity/movement.h"
#include "gfx/animation.h"
#include "gfx/draw.h"
#include "gfx/texture.h"
#include "input/mouse.h"
#include "map/map.h"
#include "map/path.h"
#include "screen/screen.h"
#include "ui/ui.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

static void draw_simple_map()
{
    texture_t *tex = gfx_texture_by_filename("basic_tiles.png");
    int sprite;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_tile_data tile = map_get(x, y);
            switch (tile.terrain_type) {
            case MAP_TERRAIN_GROUND:
                sprite = 0;
                break;
            case MAP_TERRAIN_WATER:
                sprite = 1;
                break;
            case MAP_TERRAIN_SHORE:
                sprite = 2;
                break;
            }

            vec2 pos = coords_tile_to_screen((vec2){.x = x, .y = y});
            gfx_draw(tex, sprite, pos);
        }
    }
}

static void draw_terrain_textures()
{
    texture_t *allmasks = gfx_texture_by_filename("diamond_mask.png");
    texture_t *grass = gfx_texture_by_filename("cropped/grass.png");
    texture_t *water = gfx_texture_by_filename("cropped/water.png");
    texture_t *beach = gfx_texture_by_filename("cropped/beach.png");

    texture_t *active;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_tile_data tile = map_get(x, y);
            switch (tile.terrain_type) {
            case MAP_TERRAIN_GROUND:
                active = grass;
                break;
            case MAP_TERRAIN_WATER:
                active = water;
                break;
            case MAP_TERRAIN_SHORE:
                active = beach;
                break;
            default:
                continue;
                break;
            }

            vec2 pos = coords_tile_to_screen((vec2){.x = x, .y = y});

            SDL_Rect src_rect = {.w = 64, .h = 32, .x = (x % 8) * 64, .y = (y % 8) * 32};
            SDL_Rect dst_rect = {.w = 64 * SCALE_FACTOR, .h = 32 * SCALE_FACTOR, .x = pos.x, .y = pos.y};

            SDL_RenderCopy(screen_get_renderer(), active->texture, &src_rect, &dst_rect);
        }
    }
}

static void draw_terrain_masks(vec2 pos)
{
    map_tile_data tile = map_get(pos.x, pos.y);
    if (tile.influence_adjacent == 0x0 && tile.influence_diagonal == 0x0)
        return;

    texture_t *allmasks = gfx_texture_by_filename("cropped/watershore.png");
    texture_t *grass = gfx_texture_by_filename("cropped/grass.png");
    texture_t *water = gfx_texture_by_filename("cropped/water.png");
    texture_t *beach = gfx_texture_by_filename("cropped/beach.png");
    texture_t *fg_tex;
    texture_t *bg_tex;

    switch (tile.influence_terrain) {
    case MAP_TERRAIN_GROUND:
        bg_tex = grass;
        break;
    case MAP_TERRAIN_WATER:
        bg_tex = water;
        break;
    case MAP_TERRAIN_SHORE:
        bg_tex = beach;
        break;
    }

    SDL_Texture *mt;
    SDL_Rect src_rect, dst_rect;

    // blend textures if needed
    if (tile.texture == NULL) {
        switch (tile.terrain_type) {
        case MAP_TERRAIN_GROUND:
            fg_tex = grass;
            break;
        case MAP_TERRAIN_WATER:
            fg_tex = water;
            break;
        case MAP_TERRAIN_SHORE:
            fg_tex = beach;
            break;
        }

        mt = SDL_CreateTexture(screen_get_renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 64, 32);
        SDL_SetTextureBlendMode(mt, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(screen_get_renderer(), mt);

        // mask
        SDL_Rect src_rect = {.w = 64, .h = 32, .x = tile.mask_tile.x * 64, .y = tile.mask_tile.y * 32};
        SDL_Rect dst_rect = {.w = 64, .h = 32, .x = 0, .y = 0};
        SDL_RenderCopy(screen_get_renderer(), allmasks->texture, &src_rect, &dst_rect);

        // foreground(main) texture
        src_rect = (SDL_Rect){.w = 64, .h = 32, .x = ((int)pos.x % 8) * 64, .y = ((int)pos.y % 8) * 32};
        dst_rect = (SDL_Rect){.w = 64, .h = 32, .x = 0, .y = 0};
        SDL_SetTextureBlendMode(fg_tex->texture, SDL_BLENDMODE_ADD);
        SDL_RenderCopy(screen_get_renderer(), fg_tex->texture, &src_rect, &dst_rect);
        SDL_SetTextureBlendMode(fg_tex->texture, SDL_BLENDMODE_BLEND);

        // restore
        SDL_SetRenderTarget(screen_get_renderer(), NULL);

        // cache texture
        map_set_texture(mt, pos.x, pos.y);
    } else {
        mt = tile.texture;
    }

    // background texture
    vec2 mpos = coords_tile_to_screen(pos);
    src_rect = (SDL_Rect){.w = 64, .h = 32, .x = 0, .y = 0};
    dst_rect = (SDL_Rect){.w = 64 * SCALE_FACTOR, .h = 32 * SCALE_FACTOR, .x = mpos.x, .y = mpos.y};
    SDL_RenderCopy(screen_get_renderer(), bg_tex->texture, &src_rect, &dst_rect);
    SDL_RenderCopy(screen_get_renderer(), mt, &src_rect, &dst_rect);
}

static void draw_entities()
{
    entity_t *ent;
    texture_t *tex;
    animation_t *anim;

    usize len = entity_len();
    for (usize id = 0; id < len; id++) {
        ent = entity_get(id);
        if (ent->state < 0)
            continue;
        if (ent->anims.len == 0)
            continue;

        for (i32 i = 0; i < ent->anims.len; i++) {
            if (ent->anims.anim_state[i] != ent->state)
                continue;

            anim = gfx_animation_get(ent->anims.anim_ids[i]);
            tex = gfx_texture_get(anim->texture_id);

            vec2 sc_pos = coords_world_to_screen(ent->transform.world_pos);
            sc_pos.x -= anim->offset_x;
            sc_pos.y -= anim->offset_y;

            int direction_offset = 0;
            if (ent->transform.direction != DIR_8_NONE)
                direction_offset = ent->transform.direction * anim->max_frames;

            gfx_draw(tex, anim->current_frame + direction_offset, sc_pos);
        }
    }
}

static void draw_mouse()
{
    // texture_t *tex = gfx_texture_by_filename("basic_tiles.png");
    // gfx_draw_texture_on_map(tex, 3, coords_mouse_to_tile());
}

static void draw_debug_info()
{
    char str[100];
    u8 gap = 250;
    int y = 0;

    const mouse *m = input_mouse_get();
    sprintf(str, "mouse: %d, %d", m->x, m->y);
    ui_draw_text(WINDOW_WIDTH - gap, y += 24, str, 16);

    vec2 mouse_pos_tile = coords_mouse_to_tile();
    sprintf(str, "mouse tile: %d, %d", (int)mouse_pos_tile.x, (int)mouse_pos_tile.y);
    ui_draw_text(WINDOW_WIDTH - gap, y += 25, str, 16);

    mouse_pos_tile = coords_screen_to_world();
    sprintf(str, "mouse world: %d, %d", (int)mouse_pos_tile.x, (int)mouse_pos_tile.y);
    ui_draw_text(WINDOW_WIDTH - gap, y += 24, str, 16);

    entity_t *player = entity_by_tag("player");
    sprintf(str, "player pos: %d, %d", (int)player->transform.world_pos.x, (int)player->transform.world_pos.y);
    ui_draw_text(WINDOW_WIDTH - gap, y += 24, str, 16);
}

void game_init()
{
}

void game_draw()
{
    screen_clear();

    gfx_animation_advance();
    /* draw_simple_map(); */
    draw_terrain_textures();

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            draw_terrain_masks((vec2){.x = x, .y = y});
        }
    }

    draw_entities();
    draw_mouse();
    draw_debug_info();
    /* draw_debug_path(); */

    screen_present();
}

static void handle_mouse_click()
{
    // const mouse *m = input_mouse_get();

    // if (m->click == MOUSE_DOUBLE_CLICK) {
    //     vec2 mp = coords_mouse_to_tile();
    //     entity_t *ent = entity_by_tag("player");
    //     ent->path_len = map_path_find(ent->path, ent->pos, mp);
    //     ent->path_next_index = 0;
    // }
}

void game_run()
{
    // handle_mouse_click();
    // ai_follower_update();

    time_millis now = time_get_millis();
    usize len = entity_len();
    for (usize id = 0; id < len; id++) {
        entity_t *ent = entity_get(id);
        entity_movement_advance(now, ent);
    }

    entity_sort();
}
