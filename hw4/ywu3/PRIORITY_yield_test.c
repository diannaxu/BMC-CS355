#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void priority_test(void *arg) {
    int *priority = (int *)arg;
    printf("thread with PRIORITY %d is running\n", *priority);
    thread_yield();
    printf("thread with PRIORITY %d yielded\n", *priority);
}

int main() {
    if (thread_libinit(PRIORITY) == -1) {
        printf("failed to initialize thread library\n");
        exit(EXIT_FAILURE);
    }

    int priorities[] = {1, 0, -1};
    int tids[3];

    for (int i = 0; i < 3; ++i) {
        tids[i] = thread_create(priority_test, &priorities[i], priorities[i]);
        if (tids[i] == -1) {
            printf("failed to create thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (thread_join(tids[i]) == -1) {
            printf("failed to join thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == -1) {
        printf("failed to terminate thread library\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
