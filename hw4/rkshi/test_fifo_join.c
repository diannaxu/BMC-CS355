// Author: Ruikang Shi
// test FIFO join: create threads 1,2,...,10, each thread join the next one except for thread 10
// order of printing "Thread n finished" with n from 10 to 1

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 10
#define FAILURE -1

int threads[THREAD_NUM];

void foo(void* arg) {
    int num = *((int*) arg);
    if ((num  < 10)) {
        if (thread_join(threads[num]) == FAILURE) {
            printf("join failure\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Thread %d finished\n", num);
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
