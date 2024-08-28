#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_SIZE 128

stack* stack_create() {
    stack *s = (stack*) malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "failed to allocate stack memory");
        abort();
    }

    point *nodes;
    nodes = (point*) malloc(sizeof(point) * STACK_SIZE);

    if (nodes == NULL) {
        fprintf(stderr, "failed to allocate nodes memory");
        abort();
    }

    s->nodes = nodes;
    s->max_size = STACK_SIZE;
    s->cnt = -1;

    return s;
}

void stack_push(stack *s, point elem) {
    if (s->cnt + 1 > s->max_size-1) {
        // double stack size
        int new_size = s->max_size * 2;
        point *new_data = (point*) malloc(sizeof(point) * new_size);
        if (new_data == NULL) {
            fprintf(stderr, "failed doublesize stack\n");
            abort();
        }

        for (int i = 0; i <= s->cnt; i++) {
            new_data[i] = s->nodes[i];
        }

        free(s->nodes);
        s->nodes = new_data;
        s->max_size = new_size;
    }

    s->cnt++;
    s->nodes[s->cnt] = elem;
}

void stack_sort(stack *s) {
    int swapped = 1;
    int n = s->cnt;

    while (swapped == 1) {
        swapped = 0;
        for (int i = 1; i <= n; i++) {
            if (s->nodes[i-1].f < s->nodes[i].f) {
                point l = s->nodes[i-1];
                point r = s->nodes[i];

                s->nodes[i-1] = r;
                s->nodes[i] = l;

                swapped = 1;
            }
        }
        n = n - 1;
    }
}

point stack_pop(stack *s) {
    point val = s->nodes[s->cnt];
    s->cnt--;
    return val;
}

int stack_size(stack *s) {
    return s->cnt + 1;
}

int stack_has_elem(stack *s, point elem) {
    for (int i = 0; i <= s->cnt; i++) {
        if (s->nodes[i].tile.x == elem.tile.x && s->nodes[i].tile.y == elem.tile.y) {
            return 1;
        }
    }
    return -1;
}


void stack_destory(stack *s) {
    free(s->nodes);
    free(s);
}
