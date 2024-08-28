#include "movement.h"
#include "coords/coords.h"
#include "core/direction.h"
#include "core/types.h"
#include "entity/entity.h"
#include "screen/screen.h"
#include "time/time.h"

#include <SDL2/SDL.h>
#include <stdio.h>

void entity_movement_advance(time_millis now, entity_t *ent)
{
    return;

    // if (ent->speed == 0)
    //     return;

    // if (ent->path_len > 0) {
    //     float dt = (now - ent->movement_last_updated) / 1000.0f;

    //     vec2 next_tile = ent->path[ent->path_next_index];
    //     vec2 wp = {.x = next_tile.x * DIAMOND_SIZE + 16, .y = next_tile.y * DIAMOND_SIZE + 16};

    //     direction_type dir = calc_general_direction(ent->world_pos.x, ent->world_pos.y, wp.x, wp.y);
    //     if (dir != DIR_8_NONE)
    //         ent->direction = dir;

    //     // due to isometric projection nature running in these two
    //     // direction will appear faster to the user but in 2d projection
    //     // is stays constant in every directon. So, in order to keep
    //     // character speed "consistent" on sceen we change speed value in
    //     // these directions.
    //     float speed = 64.f;
    //     if (dir == DIR_1_TOP_RIGHT || dir == DIR_5_BOTTOM_LEFT)
    //         speed = 44.f;

    //     float move_pixels = speed * ent->speed * dt;

    //     if (ent->world_pos.x > wp.x)
    //         ent->world_pos.x -= move_pixels;
    //     if (ent->world_pos.x < wp.x)
    //         ent->world_pos.x += move_pixels;
    //     if (ent->world_pos.y > wp.y)
    //         ent->world_pos.y -= move_pixels;
    //     if (ent->world_pos.y < wp.y)
    //         ent->world_pos.y += move_pixels;

    //     SDL_Rect a = {.x = ent->world_pos.x, .y = ent->world_pos.y, .w = 5, .h = 5};
    //     SDL_Rect b = {.x = wp.x - 2, .y = wp.y - 2, .w = 5, .h = 5};

    //     if (SDL_HasIntersection(&a, &b))
    //         ent->path_next_index += 1;

    //     if (ent->path_next_index >= ent->path_len) {
    //         ent->path_len = 0;
    //         ent->state = ENTITY_STATE_IDLE;
    //     } else {
    //         ent->state = ENTITY_STATE_RUN;
    //     }

    //     ent->pos.x = (int)(ent->world_pos.x / DIAMOND_SIZE);
    //     ent->pos.y = (int)(ent->world_pos.y / DIAMOND_SIZE);
    // }

    // ent->movement_last_updated = now;
}
