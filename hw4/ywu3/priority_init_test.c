#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int main() {
    if (thread_libinit(PRIORITY) == 0) {
        printf("priority initialized successfully\n");

        if (thread_libterminate() == 0) {
            printf("terminated successfully\n");
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "error: failed to terminate thread library\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "error: failed to initialize FIFO\n");
        exit(EXIT_FAILURE);
    }
}
