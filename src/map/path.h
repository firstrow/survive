#ifndef PATH_H_
#define PATH_H_

#include "core/types.h"

typedef struct {
    usize len;
    vec2 *path_tiles;
} map_path;

int map_path_find(vec2 *path, vec2 from, vec2 to);

#endif // PATH_H_
