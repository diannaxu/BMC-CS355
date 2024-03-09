#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void low_priority_task(void *arg) {
    printf("low priority task\n");
}

void medium_priority_task(void *arg) {
    printf("medium priority task\n");
}

void high_priority_task(void *arg) {
    printf("high priority task\n");
}

int main() {
    if (thread_libinit(PRIORITY) == -1) {
        printf("error: failed to initialize thread library\n");
        exit(EXIT_FAILURE);
    }

    int low_tid = thread_create(low_priority_task, NULL, 1);
    int medium_tid = thread_create(medium_priority_task, NULL, 0);
    int high_tid = thread_create(high_priority_task, NULL, -1);

    if (low_tid == -1 || medium_tid == -1 || high_tid == -1) {
        printf("error: failed to create threads\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(low_tid) == -1 || thread_join(medium_tid) == -1 || thread_join(high_tid) == -1) {
        printf("error: failed to join threads\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == -1) {
        printf("error: failed to terminate thread library\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
