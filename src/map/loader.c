#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "map/map.h"

#define MAXCHAR 1024

static char *rtrim(char *const s) {
    size_t len;
    char *cur;

    if(s && *s) {
        len = strlen(s);
        cur = s + len - 1;

        while(cur != s && isspace(*cur))
                --cur, --len;

        cur[isspace(*cur) ? 0 : 1] = '\0';
    }

    return s;
}

static map_terrain_type to_terrain_type(int idx) {
    switch (idx) {
        case 0:
            return MAP_TERRAIN_GROUND;
            break;
        case 1:
            return MAP_TERRAIN_WATER;
            break;
        case 2:
            return MAP_TERRAIN_SHORE;
            break;
        default:
            printf("should not get here\r\n");
            abort();
            break;
    }

    return -1;
}

void map_load_csv(char* fpath) {
    char row[MAXCHAR];
    char *token;

    map_reset();

    int x = 0;
    int y = 0;

    FILE *fp;
    fp = fopen(fpath, "r");

    while(feof(fp) != true) {
        fgets(row, MAXCHAR, fp);

        x = 0;
        if (y >= MAP_HEIGHT)
            break;

        token = strtok(row, ",");
        map_set_terrain_type(to_terrain_type(atoi(token)), x, y);

        while(token != NULL) {
            x++;
            token = strtok(NULL, ",");
            if (token != NULL)  {
                rtrim(token);
                map_set_terrain_type(to_terrain_type(atoi(token)), x, y);
            }
        }

        y++;
    }

    fclose(fp);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_solve_tile_influence((vec2){.x=x, .y=y});
        }
    }
}
