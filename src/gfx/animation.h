#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "core/types.h"
#include "gfx/texture.h"
#include "time/time.h"
#include <stdbool.h>

typedef struct {
    usize texture_id;
    int max_frames;
    bool loop;
    time_millis time_per_frame;
    int offset_x;
    int offset_y;

    time_millis last_updated;
    i32 current_frame;
} animation_t;

usize gfx_animation_create(animation_t anim);
void gfx_animation_destroy(usize id);
void gfx_animation_init();
void gfx_animation_advance();
animation_t *gfx_animation_get(usize id);

#endif // ANIMATION_H_
