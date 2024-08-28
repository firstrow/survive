#ifndef DRAW_H_
#define DRAW_H_

#include "core/types.h"
#include "gfx/texture.h"
#include "gfx/animation.h"

void gfx_draw(texture_t *t, int index, vec2 pos);
void gfx_draw_texture_on_map(texture_t *t, int sprite, vec2 map_pos);

#endif // DRAW_H_
