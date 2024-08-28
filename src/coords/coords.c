#include "coords.h"

#include "core/types.h"
#include "gfx/texture.h"
#include "input/mouse.h"

// mouse cursor pos to tile
vec2 coords_mouse_to_tile()
{
    vec2 pos = coords_screen_to_world();
    return (vec2){.x = (int)pos.x / 32, .y = (int)pos.y / 32};
}

// converts map tile coodrinates to screen coords
vec2 coords_tile_to_screen(vec2 v)
{
    int mx = (v.x - v.y) * 32 + camera_x;
    int my = (v.x + v.y) * 16 + camera_y;
    return (vec2){.x = mx, .y = my};
}

vec2 coords_world_to_screen(vec2 wpos)
{
    int ix = (wpos.x - wpos.y) + 32 + camera_x;
    int iy = (wpos.x + wpos.y) / 2 + camera_y;

    return (vec2){.x = ix, .y = iy};
}

vec2 coords_screen_to_world()
{
    const mouse *m = input_mouse_get();

    int x = (m->x + (m->y - camera_y) * 2 - camera_x - 32) * 0.5;
    int y = m->y - (m->x - camera_x) * 0.5 - camera_y + 16;

    return (vec2){.x = x, .y = y};
}
