#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int main() {
    if (thread_libinit(FIFO) == -1) {
        exit(EXIT_FAILURE);
    }

    int tid = thread_create(NULL, NULL, 0);
    if (tid == -1) {
        exit(EXIT_FAILURE);
    } else {
        printf("Thread created successfully with ID: %d\n", tid);
    }

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
