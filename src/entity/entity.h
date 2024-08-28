#ifndef ENTITY_H_
#define ENTITY_H_

#include "core/direction.h"
#include "core/types.h"
#include "gfx/animation.h"
#include "time/time.h"
#include <stdbool.h>

#define MAX_PATH_LEN 64
// #define MAX_STATES 64

// typedef enum {
//     ENTITY_TYPE_UNDEFINED,
//     ENTITY_UNIT,
//     ENTITY_TREE,
// } entity_type;

// typedef enum {
//     ENTITY_STATE_UNDEFINED,
//     ENTITY_STATE_IDLE,
//     ENTITY_STATE_RUN,
// } entity_state;

typedef struct {
    vec2 map_pos;
    vec2 world_pos;
    i8 direction;
} transform_c;

typedef struct {
    i32 len;
    i32 anim_ids[32];
    i32 anim_state[32];
} animation_c;

typedef struct {
    // bool active;
    // entity_type type;
    // entity_state state;
    // usize state_animation[MAX_STATES];

    // vec2 pos; // tile
    // vec2 world_pos; // sub-tile coords

    // MOVEMENT:
    // path is stored from dest point to unit start tile.
    // path_len is initallty how many tiles unit should travel.
    // by decreasing path_len unit travels.
    // if path_len = 0 means unit have arrived at destination.
    //
    // path = [1, 2, 3, ... 23];
    // path_len = 24;
    // double speed; // tiles per second
    // time_millis movement_last_updated;
    // vec2 *path;
    // int path_len;
    // int path_next_index;
    // direction_type direction;

    // main components
    usize id;
    char *tag;
    transform_c transform;
    animation_c anims;
    i32 state;
    
} entity_t;

void entity_init();
usize entity_create();
entity_t *entity_get(usize id);
entity_t *entity_by_tag(char *tag);
usize entity_len();
void entity_sort();
void entity_anim_add(entity_t *e, i32 state, usize anim_id);
direction_type entity_calc_general_direction(float x_from, float y_from, float x_to, float y_to);

#endif // ENTITY_H_
