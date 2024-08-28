#include <stdio.h>

#include "mouse.h"
#include "time/time.h"

#include <SDL2/SDL.h>

static mouse data;

int clicks = 0;
time_millis last_click;

const mouse* input_mouse_get() {
    return &data;
}

void input_mouse_set_pos(int x, int y) {
    if (x != data.x || y != data.y) {
        last_click = 0;
    }
    data.x = x;
    data.y = y;
}

void input_mouse_update_state() {
    time_millis now = time_get_millis();

    data.click = MOUSE_NONE;

    if (now - last_click >= DOUBLE_CLICK_SPEED) {
        if (clicks > 1)
            data.click = MOUSE_DOUBLE_CLICK;
        if (clicks == 1)
            data.click = MOUSE_CLICK;

        clicks = 0;
    }
}

void input_mouse_click() {
    clicks++;
    last_click = time_get_millis();
}
