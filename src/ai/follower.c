#include "ai/follower.h"
#include "entity/entity.h"
#include "map/path.h"
#include "time/time.h"

#include <stdio.h>

static time_millis last_updated;

void ai_follower_update() {
//     entity_t *player = entity_by_tag("player");
//     if (!player)
//         return;

//     entity_t *follower = entity_by_tag("follower");
//     if (!follower)
//         return;

//     bool should_update = time_get_millis() - last_updated >= 1000; 

//     if (follower->path_len == 0 || should_update) {
//         follower->path_len = map_path_find(follower->path, follower->pos, player->pos);
//         follower->path_next_index = 0;

//         last_updated = time_get_millis();
//     }
}
