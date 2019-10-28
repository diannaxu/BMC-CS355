// Author: Yuxiao Wang
// test FIFO yield: create threads 1, 2, 3, 4; main joins all, 1 yields, 3 yields
// order of printing "I'm thread <#>" should be 2, 4, 1, 3

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 4
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    if (num == 1 || num == 3) {
        thread_yield();
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
    int threads[THREAD_NUM];
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
