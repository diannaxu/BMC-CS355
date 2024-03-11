#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void thread_func(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d: %d\n", id, i);
        thread_yield();
    }
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        printf("thread_libinit failed\n");
        exit(EXIT_FAILURE);
    }

    int ids[2] = {0, 1}; // Initialize an array with IDs for each thread
    int tid1 = thread_create(thread_func, &ids[0], 0);
    int tid2 = thread_create(thread_func, &ids[1], 0);

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

    printf("Yield test passed\n");
    exit(EXIT_SUCCESS);
}
