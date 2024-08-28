cmake_minimum_required(VERSION 3.7)

set(CMAKE_BUILD_TYPE Debug)
set(SHORT_NAME survive)
project(${SHORT_NAME} C)

find_package(Lua 5.4 REQUIRED)
include_directories(include src ${LUA_INCLUDE_DIR})

# file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/cwalk/cwalk.c
    ${PROJECT_SOURCE_DIR}/include/array_list/array_list.c
    ${PROJECT_SOURCE_DIR}/src/core/config.c
    ${PROJECT_SOURCE_DIR}/src/core/print.c

    ${PROJECT_SOURCE_DIR}/src/gfx/texture.c
    ${PROJECT_SOURCE_DIR}/src/gfx/animation.c
    ${PROJECT_SOURCE_DIR}/src/gfx/draw.c

    ${PROJECT_SOURCE_DIR}/src/screen/screen.c
    ${PROJECT_SOURCE_DIR}/src/coords/coords.c
    ${PROJECT_SOURCE_DIR}/src/game/game.c

    ${PROJECT_SOURCE_DIR}/src/entity/entity.c
    ${PROJECT_SOURCE_DIR}/src/entity/movement.c

    ${PROJECT_SOURCE_DIR}/src/input/keyboard.c
    ${PROJECT_SOURCE_DIR}/src/input/mouse.c

    ${PROJECT_SOURCE_DIR}/src/map/map.c
    ${PROJECT_SOURCE_DIR}/src/map/loader.c
    ${PROJECT_SOURCE_DIR}/src/map/path.c
    ${PROJECT_SOURCE_DIR}/src/map/stack.c

    ${PROJECT_SOURCE_DIR}/src/ai/follower.c

    ${PROJECT_SOURCE_DIR}/src/lua_engine/lua_engine.c
    ${PROJECT_SOURCE_DIR}/src/lua_engine/fs.c

    ${PROJECT_SOURCE_DIR}/src/time/time.c
    ${PROJECT_SOURCE_DIR}/src/ui/ui.c
    ${PROJECT_SOURCE_DIR}/src/main/main.c
)

add_executable(${SHORT_NAME} ${SOURCE_FILES})

target_link_libraries(${SHORT_NAME} m)

find_package(SDL2 REQUIRED)
target_link_libraries(${SHORT_NAME} SDL2)

find_package(SDL2_ttf REQUIRED)
target_link_libraries(${SHORT_NAME} SDL2_ttf)

find_package(SDL2_image REQUIRED)
target_link_libraries(${SHORT_NAME} SDL2_image)

target_link_libraries(${SHORT_NAME} ${LUA_LIBRARIES})

find_package (Threads REQUIRED)
target_link_libraries(${SHORT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(
    ${SHORT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/swig.o
)

