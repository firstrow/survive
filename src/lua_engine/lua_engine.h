#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H

void lua_engine_init();
void lua_engine_reload(char *filename);
void lua_call_update(float dt);

#endif 
