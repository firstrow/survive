#ifndef STACK_H_
#define STACK_H_

#include "core/types.h"

typedef struct point {
    vec2 tile;

    int g, h;
    int f; // g + h

    struct point* parent;
} point;

typedef struct {
    point *nodes;
    int max_size;
    int cnt;
} stack;

stack* stack_create();
void stack_push(stack *s, point elem);
point stack_pop(stack *s);
int stack_size(stack *s);
void stack_sort(stack *s);
int stack_has_elem(stack *s, point elem);
void stack_destory(stack *s);

#endif // STACK_H_
