#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int main(void) {
    if (thread_libinit(FIFO) == -1)
        exit(EXIT_FAILURE);

    int tid = thread_create(NULL, NULL, 0);
    if (tid == -1) {
        thread_libterminate();
        exit(EXIT_FAILURE);
    }

    if (thread_join(tid) == -1) {
        thread_libterminate();
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == -1)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}
