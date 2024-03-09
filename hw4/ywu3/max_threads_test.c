#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void empty(void *arg) {
    printf("");
}

int main() {
    int max_threads;
    printf("enter the maximum number of threads: ");
    scanf("%d", &max_threads);

    if (thread_libinit(FIFO) == -1) {
        fprintf(stderr, "error: thread library initialization failed\n");
        exit(EXIT_FAILURE);
    }

    int thread_ids[max_threads];
    for (int i = 0; i < max_threads; i++) {
        int *arg = malloc(sizeof(int));
        if (arg == NULL) {
            fprintf(stderr, "error: memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        *arg = i;
        thread_ids[i] = thread_create(empty, arg, 0);
        if (thread_ids[i] == -1) {
            fprintf(stderr, "error: thread creation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < max_threads; i++) {
        if (thread_join(thread_ids[i]) == -1) {
            fprintf(stderr, "error: thread join failed\n");
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == -1) {
        fprintf(stderr, "error: thread library termination failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
