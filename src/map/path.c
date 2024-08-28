#include "path.h"
#include "core/types.h"
#include "entity/entity.h"
#include "math.h"
#include <stdlib.h>

#include "map/stack.h"
#include "map/map.h"

static vec2 zero = {.x = -1, .y = -1};

static void reverse(vec2 *arr, int n)
{
    vec2 aux[n];

    for (int i = 0; i < n; i++)
        aux[n - 1 - i] = arr[i];

    for (int i = 0; i < n; i++)
        arr[i] = aux[i];
}

point *neighbors(point p) {
    static point result[8];

    vec2 n[8] = {
        {.x=p.tile.x-1, .y=p.tile.y-1}, // 0
        {.x=p.tile.x,   .y=p.tile.y-1}, // 1
        {.x=p.tile.x+1, .y=p.tile.y-1}, // 2
        {.x=p.tile.x+1, .y=p.tile.y},   // 3
        {.x=p.tile.x+1, .y=p.tile.y+1}, // 4
        {.x=p.tile.x,   .y=p.tile.y+1}, // 5
        {.x=p.tile.x-1, .y=p.tile.y+1}, // 6
        {.x=p.tile.x-1, .y=p.tile.y},   // 7
    };

    for (int i = 0; i < 8; i++) {
        if (!map_check_bounds(n[i]))
            continue;

        map_tile_data tile = map_get(n[i].x, n[i].y);
        switch (tile.terrain_type) {
            case MAP_TERRAIN_GROUND:
            case MAP_TERRAIN_SHORE:
                result[i] = (point){.tile=n[i]};
                break;
            default:
                result[i] = (point){.tile=zero};
                break;
        }
    }

    return result;
}

// https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
int h(point start, point end) {
    int D = 1;
    int D2 = 2;
    int dx = abs(start.tile.x - end.tile.x);
    int dy = abs(start.tile.y - end.tile.y);
    return D * (dx + dy) + (D2 - 2 * D) * MIN(dx, dy);
    /* return D * sqrt(dx * dx + dy * dy); */
}

int map_path_find(vec2 *path, vec2 from_tile, vec2 dest_tile) {
    point start = {.tile = from_tile};
    point goal = {.tile = dest_tile};

    stack *open = stack_create();
    stack *closed = stack_create();
    stack_push(open, start);

    point current;
    bool found = false;
    while (stack_size(open) > 0) {
        stack_sort(open);
        current = stack_pop(open);

        if (current.tile.x == goal.tile.x && current.tile.y == goal.tile.y) {
            found = true;
            break;
        }

        stack_push(closed, current);

        point *n = neighbors(current);
        for (int i = 0; i < 8; i++) {
            if (n[i].tile.x < 0)
                continue;
            if (stack_has_elem(open, n[i]) == 1 || stack_has_elem(closed, n[i]) == 1)
                continue;

            /* n[i].g = h(current, n[i]); */
            n[i].g = current.g + 1;
            n[i].h = h(n[i], goal);
            n[i].f = n[i].g + n[i].h;

            n[i].parent = (point*)malloc(sizeof(point));
            memcpy(n[i].parent, &current, sizeof(point));

            stack_push(open, n[i]);
        }
    }

    stack_destory(open);
    stack_destory(closed);

    int num_tiles = 0;
    if (found) {
        point p = current;
        while(p.parent != NULL) {
            path[num_tiles] = p.tile;
            num_tiles++;
            if (num_tiles >= MAX_PATH_LEN)
                break;
            p = *p.parent;
        }
        reverse(path, num_tiles);
    }
    return num_tiles;
}

