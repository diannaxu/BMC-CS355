#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void thread_func() {
    printf("Thread running\n");
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        printf("thread_libinit failed\n");
        exit(EXIT_FAILURE);
    }

    int tid = thread_create(thread_func, NULL, 0);
    if (tid == -1) {
        printf("thread_create failed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid) == -1) {
        printf("thread_join failed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid) == -1) {
        printf("Joining an already joined thread failed as expected\n");
    } else {
        printf("Joining an already joined thread should not succeed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == -1) {
        printf("thread_libterminate failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Multiple joins test passed\n");
    exit(EXIT_SUCCESS);
}