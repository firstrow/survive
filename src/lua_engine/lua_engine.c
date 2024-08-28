#include "lua_engine/lua_engine.h"
#include "core/config.h"
#include "entity/entity.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>

extern int luaopen_game(lua_State *L);

static lua_State *L;

// static int load_texture(lua_State *L)
// {
//     printf("C load texture\n");
//     double d = lua_tonumber(L, 1);
//     lua_pushnumber(L, 22);
//     return 1;
// }

// static const struct luaL_Reg mylib[] = {
//     {"ddd", load_texture},
//     {NULL, NULL}};

entity_t *l_entity_by_tag(char *name)
{
    return entity_by_tag(name);
}

void lua_engine_init()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    // luaL_newlib(L, mylib);
    // lua_setglobal(L, "engine");

    // lua_pushcfunction(L, load_texture);
    // lua_setglobal(L, "load_texture");

    char buf[FILENAME_MAX];
    sprintf(buf, "package.path = package.path .. \";%s/scripts/?.lua\"", core_config_get_game_path());
    luaL_dostring(L, buf);

    luaopen_game(L);

    if (luaL_dofile(L, core_config_get_scripts_path("init.lua")) != LUA_OK) {
        printf("%s\n", lua_tostring(L, -1));
        abort();
    }
}

void lua_call_update(float dt) {
    lua_getglobal(L, "Update");
    lua_pushnumber(L, dt);
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        printf("lua Update call failed: %s\n", lua_tostring(L, -1));
    }
}

void lua_engine_reload(char *filename)
{
    printf("reloading %s\n", filename);
    lua_getglobal(L, "Reload");
    lua_pushstring(L, filename);
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        printf("lua reload failed: %s\n", lua_tostring(L, -1));
    }
}
