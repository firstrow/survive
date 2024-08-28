#include "entity.h"
#include "array_list/array_list.h"
#include "coords/coords.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static array_list *entity_storage;

void entity_init()
{
    entity_storage = array_list_create(sizeof(entity_t), 128);
}

usize entity_create()
{
    entity_t *ee = calloc(1, sizeof(entity_t));
    usize id = array_list_append(entity_storage, ee);
    entity_get(id)->id = id;
    free(ee);
    return id;
}

entity_t *entity_get(usize id)
{
    return array_list_get(entity_storage, id);
}

entity_t *entity_by_tag(char *tag)
{
    usize len = entity_len();
    for (usize id = 0; id < len; id++) {
        entity_t *ent = entity_get(id);
        if (ent == NULL)
            continue;
        if (ent->tag == NULL)
            continue;
        if (strcmp(tag, ent->tag) == 0)
            return ent;
    }
    return NULL;
}

usize entity_len()
{
    return entity_storage->len;
}

static int compare(const void *a, const void *b)
{
    // entity_t *ea = (entity_t *)a;
    // entity_t *eb = (entity_t *)b;
    // return (ea->world_pos.y > eb->world_pos.y);
    return 0;
}

void entity_sort()
{
    // qsort(entity_storage->items, entity_storage->len, sizeof(entity_t), compare);
}

void entity_anim_add(entity_t *e, i32 state, usize anim_id)
{
    e->anims.anim_ids[e->anims.len] = anim_id;
    e->anims.anim_state[e->anims.len] = state;
    e->anims.len++;
}

direction_type entity_calc_general_direction(float x_from, float y_from, float x_to, float y_to)
{
    if (x_from < x_to) {
        if (y_from > y_to) {
            return DIR_1_TOP_RIGHT;
        } else if (y_from == y_to) {
            return DIR_2_RIGHT;
        } else if (y_from < y_to) {
            return DIR_3_BOTTOM_RIGHT;
        }
    } else if (x_from == x_to) {
        if (y_from > y_to) {
            return DIR_0_TOP;
        } else if (y_from < y_to) {
            return DIR_4_BOTTOM;
        }
    } else if (x_from > x_to) {
        if (y_from > y_to) {
            return DIR_7_TOP_LEFT;
        } else if (y_from == y_to) {
            return DIR_6_LEFT;
        } else if (y_from < y_to) {
            return DIR_5_BOTTOM_LEFT;
        }
    }
    return DIR_8_NONE;
}
