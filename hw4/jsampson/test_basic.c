#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void thread_func(void *arg) {
    int thread_id = *((int *)arg);
    printf("Thread %d running\n", thread_id);
    printf("Thread %d finished\n", thread_id);
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        printf("thread_libinit failed\n");
        exit(EXIT_FAILURE);
    }

    int *arg1 = malloc(sizeof(int));
    *arg1 = 0;
    int tid1 = thread_create(thread_func, arg1, 0);

    int *arg2 = malloc(sizeof(int));
    *arg2 = 1;
    int tid2 = thread_create(thread_func, arg2, 0);

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

    printf("Basic test passed\n");
    exit(EXIT_SUCCESS);
}
