#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "userthread.h"

void short_task() {
    printf("Short task running\n");
    usleep(100000);  // Sleep for 100ms
}

void long_task() {
    printf("Long task running\n");
    usleep(300000);  // Sleep for 300ms
}

int main() {
    if (thread_libinit(SJF) == -1) {
        printf("thread_libinit failed\n");
        exit(EXIT_FAILURE);
    }

    int tid1 = thread_create(long_task, NULL, 0);
    int tid2 = thread_create(short_task, NULL, 0);

    if (tid1 == -1 || tid2 == -1) {
        printf("thread_create failed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid1) == -1 || thread_join(tid2) == -1) {
        printf("thread_join failed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == -1) {
        printf("thread_libterminate failed\n");
        exit(EXIT_FAILURE);
    }

    printf("SJF test passed\n");
    exit(EXIT_SUCCESS);
}