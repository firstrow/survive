#include "assert.h"
#include "coords/coords.h"
#include "core/config.h"
#include "core/types.h"
#include "entity/entity.h"
#include "game/game.h"
#include "gfx/animation.h"
#include "gfx/texture.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "lua_engine/fs.h"
#include "lua_engine/lua_engine.h"
#include "map/loader.h"
#include "map/map.h"
#include "screen/screen.h"
#include "time/time.h"
#include "ui/ui.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

int tile_width = 64;
int tile_height = 32;
int camera_x = 400;
int camera_y = 0;
double SCALE_FACTOR = 1.0f;
int DIAMOND_SIZE = 32;

static void update_factor()
{
    tile_width = 64 * SCALE_FACTOR;
    tile_height = 32 * SCALE_FACTOR;
    camera_x = 0;
    camera_y = 0;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    SCALE_FACTOR = 1.0f;
    tile_width = 64 * SCALE_FACTOR;
    tile_height = 32 * SCALE_FACTOR;

    int running = 1;

    core_config_set_game_path("/home/andrew/code/survive");
    map_load_csv(core_config_get_asset_path("survice_map.csv"));
    screen_init();
    gfx_texture_init();
    gfx_animation_init();
    game_init();
    entity_init();
    input_keyboard_init();
    ui_init();
    lua_engine_init();

    entity_t *player = entity_get(entity_create());
    // player->state = 0;
    // player->transform.world_pos.x = 100;
    // player->transform.world_pos.y = 100;
    // player->tag = "player";

    // entity_anim_add(
    //     player,
    //     0,
    //     gfx_animation_create((animation_t){
    //         .texture_id = gfx_texture_id_by_filename("character/run.png"),
    //         .max_frames = 19,
    //         .loop = true,
    //         .time_per_frame = 40,
    //         .offset_x = 32,
    //         .offset_y = 46,
    //     }));

    lua_engine_fs_start(core_config_get_scripts_path(""));

    float dt;
    time_millis now = SDL_GetTicks();
    time_millis last_updated = 0.f;
    SDL_Event event;
    while (running) {
        now = SDL_GetTicks();
        time_set_millis(now);

        dt = (now - last_updated) / 1000.0f;

        input_mouse_update_state();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEMOTION:
                input_mouse_set_pos(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONUP:
                input_mouse_click();
                break;
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = 0;
                    break;
                case SDLK_LEFT:
                    camera_x += tile_width;
                    break;
                case SDLK_RIGHT:
                    camera_x -= tile_width;
                    break;
                case SDLK_UP:
                    camera_y += tile_height;
                    break;
                case SDLK_DOWN:
                    camera_y -= tile_height;
                    break;
                case SDLK_EQUALS:
                    SCALE_FACTOR += 0.1;
                    update_factor();
                    break;
                case SDLK_MINUS:
                    SCALE_FACTOR -= 0.1;
                    update_factor();
                    break;
                }
                break;
            default:
                break;
            }
        }

        input_keyboard_update();

        lua_call_update(dt);
        game_run();
        game_draw();

        last_updated = time_get_millis();
    }

    screen_destroy();
    lua_engine_fs_stop();

    return 0;
}
