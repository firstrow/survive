#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <cwalk/cwalk.h>
#include <string.h>

#define ASSETS_DIR "assets"
#define SCRIPTS_DIR "scripts"

static struct {
    char* game_path;
} config;

void core_config_set_game_path(char* p) {
    config.game_path = p;
}

char* core_config_get_game_path() {
    return config.game_path;
}

char* core_config_get_asset_path(char* filename) {
    char buf[FILENAME_MAX];
    const char *paths[4];
    paths[0] = config.game_path;
    paths[1] = ASSETS_DIR;
    paths[2] = filename;
    paths[3] = NULL;
    cwk_path_join_multiple(paths, buf, sizeof(buf));
    return strdup(buf);;
}

char* core_config_get_scripts_path(char* filename) {
    char buf[FILENAME_MAX];
    const char *paths[4];
    paths[0] = config.game_path;
    paths[1] = SCRIPTS_DIR;
    paths[2] = filename;
    paths[3] = NULL;
    cwk_path_join_multiple(paths, buf, sizeof(buf));
    return strdup(buf);;
}
