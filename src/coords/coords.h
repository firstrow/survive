#ifndef COORDS_H_
#define COORDS_H_

#include "core/types.h"

vec2 coords_mouse_to_tile();
vec2 coords_tile_to_screen(vec2 coords);
vec2 coords_world_to_screen(vec2 wpos);
vec2 coords_screen_to_world();

#endif // COORDS_H_
