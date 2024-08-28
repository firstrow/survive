#include "animation.h"
#include "array_list/array_list.h"
#include "core/types.h"
#include "gfx/texture.h"
#include "time/time.h"
#include <stdlib.h>

static array_list *animation_storage;

void gfx_animation_init()
{
    void *buf = malloc(122);
    animation_storage = array_list_create(sizeof(animation_t), 128);
}

usize gfx_animation_create(animation_t anim)
{
    // TODO: reuse non-active ids
    return array_list_append(animation_storage, &anim);
}

void gfx_animation_destroy(usize id)
{
    // TODO: disable and ignore frame advancing
}

animation_t *gfx_animation_get(usize id)
{
    return array_list_get(animation_storage, id);
}

void gfx_animation_advance()
{
    time_millis now = time_get_millis();

    animation_t *anim;

    for (int id = 0; id < animation_storage->len; id++) {
        anim = gfx_animation_get(id);
        if (anim->time_per_frame == 0)
            continue;

        if (now >= anim->last_updated + anim->time_per_frame) {
            anim->current_frame++;

            // TODO: last frame now displayed?
            if (anim->current_frame == anim->max_frames)
                anim->current_frame = 0;

            anim->last_updated = now;
        }
    }
}
