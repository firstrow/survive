#include "map.h"
#include "core/types.h"
#include <SDL2/SDL_stdinc.h>
#include <stdbool.h>

static map_tile_data map_data[MAP_HEIGHT][MAP_WIDTH];

void map_reset()
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_data[y][x] = (map_tile_data){.terrain_type = MAP_TERRAIN_GROUND};
        }
    }
}

map_tile_data map_get(int x, int y)
{
    if (!map_check_bounds((vec2){.x = x, .y = y}))
        return (map_tile_data){};
    return map_data[y][x];
}

void map_set_terrain_type(int type, int x, int y)
{
    map_data[y][x].terrain_type = type;
}

void map_set_texture(SDL_Texture *t, int x, int y)
{
    map_data[y][x].texture = t;
}

bool map_check_bounds(vec2 pos)
{
    if (pos.x < 0 || pos.y < 0)
        return false;

    if ((int)pos.x > MAP_WIDTH - 1 || (int)pos.y > MAP_HEIGHT - 1)
        return false;

    return true;
}

bool map_check_world_bounds(float x, float y)
{
    if (x < 0 || y < 0)
        return false;

    if (x > MAP_WIDTH * DIAMOND_SIZE || y > MAP_HEIGHT * DIAMOND_SIZE)
        return false;

    return true;
}

//    0
//  7   1      => 8 neighbours that have influence on
// 6   @   2         the mask id selection.
//   5   3
//     4
void map_solve_tile_influence(vec2 p)
{
    map_tile_data *self = &map_data[(int)p.y][(int)p.x];
    map_tile_data *other;

    vec2 n[8] = {
        {.x = p.x - 1, .y = p.y - 1}, // 0
        {.x = p.x, .y = p.y - 1},     // 1
        {.x = p.x + 1, .y = p.y - 1}, // 2
        {.x = p.x + 1, .y = p.y},     // 3
        {.x = p.x + 1, .y = p.y + 1}, // 4
        {.x = p.x, .y = p.y + 1},     // 5
        {.x = p.x - 1, .y = p.y + 1}, // 6
        {.x = p.x - 1, .y = p.y},     // 7
    };

    for (int i = 0; i < 8; i++) {
        if (!map_check_bounds(n[i]))
            continue;

        other = &map_data[(int)n[i].y][(int)n[i].x];

        if (self->terrain_type > other->terrain_type)
            continue;

        if (self->terrain_type != other->terrain_type) {
            switch (i) {
            case 0:
            case 2:
            case 4:
            case 6:
                self->influence_diagonal |= (1 << i);
                break;
            default:
                self->influence_adjacent |= (1 << i);
                break;
            }

            self->influence_tiles[i] = n[i];
            self->influence_terrain = other->terrain_type;
        }
    }

    int adjacent_mask_id = -1;
    vec2 mask_tile = {.x = -1, .y = -1};

    // this one should be extracted into a func
    // mask_id to mask_tile
    switch (self->influence_adjacent) {
    case 0x08:                // 0b00001000
        adjacent_mask_id = 0; // 0..3
        mask_tile = (vec2){.x = 0, .y = 1};
        break;
    case 0x02:                // 0b00000010
        adjacent_mask_id = 4; // 4..7
        mask_tile = (vec2){.x = 5, .y = 7};
        break;
    case 0x20:                // 0b00100000
        adjacent_mask_id = 8; // 8..11
        mask_tile = (vec2){.x = 4, .y = 0};
        break;
    case 0x80:                 // 0b10000000
        adjacent_mask_id = 12; // 12..15
        mask_tile = (vec2){.x = 7, .y = 1};
        break;
    case 0x22: // 0b00100010
        adjacent_mask_id = 20;
        mask_tile = (vec2){.x = 1, .y = 3};
        break;
    case 0x88: // 0b10001000
        adjacent_mask_id = 21;
        mask_tile = (vec2){.x = 4, .y = 6};
        break;
    case 0xA0: // 0b10100000
        adjacent_mask_id = 22;
        mask_tile = (vec2){.x = 4, .y = 3};
        break;
    case 0x82: // 0b10000010
        adjacent_mask_id = 23;
        mask_tile = (vec2){.x = 4, .y = 2};
        break;
    case 0x28: // 0b00101000
        adjacent_mask_id = 24;
        mask_tile = (vec2){.x = 5, .y = 3};
        break;
    case 0x0A: // 0b00001010
        adjacent_mask_id = 25;
        mask_tile = (vec2){.x = 5, .y = 2};
        break;
    case 0x2A: // 0b00101010
        adjacent_mask_id = 26;
        mask_tile = (vec2){.x = 2, .y = 3};
        break;
    case 0xA8: // 0b10101000
        adjacent_mask_id = 27;
        mask_tile = (vec2){.x = 2, .y = 1};
        break;
    case 0xA2: // 0b10100010
        adjacent_mask_id = 28;
        mask_tile = (vec2){.x = 6, .y = 5};
        break;
    case 0x8A: // 0b10001010
        adjacent_mask_id = 29;
        mask_tile = (vec2){.x = 4, .y = 5};
        break;
    case 0xAA: // 0b10101010
        adjacent_mask_id = 30;
        mask_tile = (vec2){.x = 2, .y = 5};
        break;
    }

    if (adjacent_mask_id == -1) {
        switch (self->influence_diagonal) {
        case 0x10:
            mask_tile = (vec2){.x = 0, .y = 0};
            break;
        case 0x40:
            mask_tile = (vec2){.x = 7, .y = 0};
            break;
        case 0x1:
            mask_tile = (vec2){.x = 7, .y = 7};
            break;
        case 0x4:
            mask_tile = (vec2){.x = 0, .y = 7};
            break;
        case 0x14:
            mask_tile = (vec2){.x = 0, .y = 3};
            break;
        case 0x50:
            mask_tile = (vec2){.x = 2, .y = 0};
            break;
        case 0x41:
            mask_tile = (vec2){.x = 7, .y = 5};
            break;
        case 0x5:
            mask_tile = (vec2){.x = 4, .y = 7};
            break;
        default:
            /* printf("no diagonal mask found: %d %d\r\n", p.x, p.y); */
            break;
        }
    }

    self->mask_tile = mask_tile;
}
