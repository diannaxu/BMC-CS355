// Author: Yuxiao Wang
// test SJF yield: every other thread yields after sleeping 10 ms; since the estimated runtime
// will be much less than the default (half of the quantum - 50ms), the same thread will be
// selected to run immediately
// order of printing "I'm thread <#>" should be 1, 2, ..., 10

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "userthread.h"

#define THREAD_NUM 10
#define SLEEP_MS 10
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    poll(NULL, 0, SLEEP_MS);
    if (num % 2 == 0) {
        thread_yield();
    }
    printf("I'm thread %d\n", num);
}

int main(int argc, char** argv) {
    if (thread_libinit(SJF) == FAILURE) {
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
            printf("join failure\n");
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == FAILURE) {
        printf("term failure\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
