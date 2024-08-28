#ifndef MOUSE_H_
#define MOUSE_H_

#include "time/time.h"

typedef enum {
    MOUSE_NONE,
    MOUSE_CLICK,
    MOUSE_DOUBLE_CLICK,
} mouse_state;

typedef struct {
    int x;
    int y;
    mouse_state click;
} mouse;

#define DOUBLE_CLICK_SPEED 250

const mouse* input_mouse_get();
void input_mouse_set_pos(int x, int y);
void input_mouse_click();
void input_mouse_update_state();

#endif // MOUSE_H_
