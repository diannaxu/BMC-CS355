#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void thread_func(void *arg) {
    printf("Thread %d executing\n", *(int *)arg);
}

int main() {
    int tid1, tid2, tid3;

    if (thread_libinit(PRIORITY) == -1) {
        printf("thread_libinit failed\n");
        exit(EXIT_FAILURE);
    }

    tid1 = thread_create(thread_func, &tid1, 1);
    tid2 = thread_create(thread_func, &tid2, 2);
    tid3 = thread_create(thread_func, &tid3, 3);

    if (tid1 == -1 || tid2 == -1 || tid3 == -1) {
        printf("thread_create failed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid1) == -1 || thread_join(tid2) == -1 || thread_join(tid3) == -1) {
        printf("thread_join failed\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == -1) {
        printf("thread_libterminate failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Priority test passed\n");
    exit(EXIT_SUCCESS);
}