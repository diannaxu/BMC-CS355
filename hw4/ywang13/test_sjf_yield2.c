// Author: Yuxiao Wang
// test SJF yield: the 1st thread will sleep 300 ms and then yield in each iteration,
// and 200ms for the 2nd thread, 100 ms for the 3rd thread. The scheduler should learn
// that the 3rd thread is taking least time, and then the 2nd, the 1st
// order of printing "I'm thread <#>" should be 3, 2, 1

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "userthread.h"

#define THREAD_NUM 3
#define SLEEP_MS 100
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    for (int i = 0; i < 5; ++i) {
        poll(NULL, 0, (4 - num) * SLEEP_MS);
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
