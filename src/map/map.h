#ifndef MAP_H_
#define MAP_H_

#include "core/types.h"
#include "stdbool.h"
#include "SDL2/SDL.h"

#define MAP_WIDTH 60
#define MAP_HEIGHT 60

// for now order is also terrain priority for masking
typedef enum {
    MAP_TERRAIN_SHORE,
    MAP_TERRAIN_GROUND,
    MAP_TERRAIN_WATER,
} map_terrain_type;

typedef struct {
    map_terrain_type terrain_type;

    // influence
    map_terrain_type influence_terrain;
    u8 influence_adjacent;
    u8 influence_diagonal;
    vec2 influence_tiles[8];
    vec2 mask_tile;
    SDL_Texture *texture;

} map_tile_data;

void map_reset();
map_tile_data map_get(int x, int y);
void map_set_terrain_type(int type, int x, int y);
void map_set_texture(SDL_Texture *t, int x, int y);
bool map_check_bounds(vec2 pos);
void map_solve_tile_influence(vec2 pos);
bool map_check_world_bounds(float x, float y);

#endif // MAP_H_

