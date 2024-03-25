#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void test(void *arg) {
    int *sjf = (int *)arg;
    printf("thread with SJF %d is running\n", *sjf);
    thread_yield();
    printf("thread with SJF %d yielded\n", *sjf);
}

int main() {
    if (thread_libinit(SJF) == -1) {
        printf("error: failed to initialize SJF\n");
        exit(EXIT_FAILURE);
    }

    int tids[3];
    int args[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        tids[i] = thread_create(test, &args[i], 0);
        if (tids[i] == -1) {
            printf("error: failed to create thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (thread_join(tids[i]) == -1) {
            printf("error: failed to join thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == -1) {
        printf("error: failed to terminate thread library\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
