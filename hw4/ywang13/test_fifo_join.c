// Author: Yuxiao Wang
// test FIFO join: create threads 1, 2, 3; main joins all; 1 joins 2; 2 creates 4, then joins 3.
// order of printing "I'm thread <#>" should be 3, 4, 2, 1

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 3
#define FAILURE -1

int threads[THREAD_NUM];

void foo(void* arg) {
    int num = *((int*) arg);
    if (num == 1) {
        if (thread_join(threads[1]) == FAILURE) {
            printf("join failure\n");
            exit(EXIT_FAILURE);
        }
    } else if (num == 2) {
        int four = 4;
        if (thread_create(foo, &four, 0) == FAILURE) {
            printf("create failure\n");
            exit(EXIT_FAILURE);
        }

        if (thread_join(threads[2]) == FAILURE) {
            printf("join failure\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("I'm thread %d\n", num);
}

int main(int argc, char** argv) {
    if (thread_libinit(FIFO) == FAILURE) {
        printf("init failure\n");
        exit(EXIT_FAILURE);
    }

    // thread #
    int num[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i) {
        num[i] = i + 1;
    }

    // create threads
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i] = thread_create(foo, num + i, 0);
        if (threads[i] == FAILURE) {
            printf("create failure\n");
            exit(EXIT_FAILURE);
        }
    }

    // join threads
    for (int i = 0; i < THREAD_NUM; ++i) {
        if (thread_join(threads[i]) == FAILURE) {
            printf("create failure\n");
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == FAILURE) {
        printf("term failure\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
