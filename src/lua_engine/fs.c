#include "lua_engine/lua_engine.h"
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>

#define MAX_EVENTS 1024
#define LEN_NAME 16
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (MAX_EVENTS * (EVENT_SIZE + LEN_NAME))

static int fd, wd;
static char *path_to_be_watched;

void lua_engine_fs_stop()
{
    inotify_rm_watch(fd, wd);
    close(fd);
    printf("stopped lua fs watcher\n");
}

void *thread_func(void *vargp)
{
    signal(SIGINT, lua_engine_fs_stop);

    fd = inotify_init();

    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
        printf("fcntl set failed\n");
        abort();
    }

    wd = inotify_add_watch(fd, path_to_be_watched, IN_MODIFY | IN_CREATE | IN_DELETE);

    if (wd == -1) {
        printf("Could not watch : %s\n", path_to_be_watched);
    } else {
        printf("Watching : %s\n", path_to_be_watched);
    }

    while (1) {
        sleep(1 * 0.5);

        int i = 0, length;
        char buffer[BUF_LEN];

        length = read(fd, buffer, BUF_LEN);

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];

            if (event->len) {
                if (event->mask & IN_CREATE) {
                    if (event->mask & IN_ISDIR) {
                    } else {
                    }
                } else if (event->mask & IN_DELETE) {
                    if (event->mask & IN_ISDIR) {
                    } else {
                    }
                } else if (event->mask & IN_MODIFY) {
                    if (event->mask & IN_ISDIR) {
                    } else {
                        lua_engine_reload(event->name);
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }
}

void lua_engine_fs_start(char *p)
{
    pthread_t tid;
    path_to_be_watched = p;
    pthread_create(&tid, NULL, thread_func, NULL);
}
