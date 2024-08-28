#include "keyboard.h"
#include "time/time.h"

#include <SDL2/SDL.h>

#define N 13

static int sdl_codes[N];
static int state[N] = {0};
static time_millis press_time[N] = {0};
static time_millis wait_time[N] = {0};

void input_keyboard_init()
{
    sdl_codes[KEY_UP] = SDL_GetScancodeFromName("w");
    sdl_codes[KEY_LEFT] = SDL_GetScancodeFromName("a");
    sdl_codes[KEY_DOWN] = SDL_GetScancodeFromName("s");
    sdl_codes[KEY_RIGHT] = SDL_GetScancodeFromName("d");
    sdl_codes[KEY_CROUCH] = SDL_GetScancodeFromName("c");
}

static void update_key_state(const Uint8 *sdl_kstate, INPUT_KEY k)
{
    Uint8 new_state = sdl_kstate[sdl_codes[k]];

    if (new_state) {
        if (state[k]) {
            state[k] = K_HOLD;
        } else {
            press_time[k] = time_get_millis();
            wait_time[k] = 250;
            state[k] = K_PRESSED;
        }
    } else {
        if (state[k] && state[k] != K_RELEASED) {
            state[k] = K_RELEASED;
        } else {
            state[k] = K_UNPRESSED;
        }
    }
}

void input_keyboard_update()
{
    const Uint8 *sdl_kstate = SDL_GetKeyboardState(NULL);

    update_key_state(sdl_kstate, KEY_UP);
    update_key_state(sdl_kstate, KEY_RIGHT);
    update_key_state(sdl_kstate, KEY_DOWN);
    update_key_state(sdl_kstate, KEY_LEFT);
    update_key_state(sdl_kstate, KEY_CROUCH);
}

bool input_key(INPUT_KEY k)
{
    return state[k] > 0;
}

bool input_key_hold(INPUT_KEY k)
{
    if (state[k] == K_PRESSED) {
        return true;
    }

    if (state[k] == K_HOLD) {
        if (time_get_millis() - press_time[k] >= wait_time[k]) {
            press_time[k] = time_get_millis();
            wait_time[k] = 33;
            return true;
        }
    }

    return false;
}
