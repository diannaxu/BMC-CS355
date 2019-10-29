// Author: Yuxiao Wang
// test several bad operations, should not crash or memleak

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "userthread.h"

#define THREAD_NUM 10
#define FAILURE -1
#define SLEEP_MS 100

void foo(void* arg) {
    if (thread_join(-1) != FAILURE) {
        printf("shouldn't join");
        exit(EXIT_FAILURE);
    }
    poll(NULL, 0, SLEEP_MS);
    if (thread_libterminate() != FAILURE) {
        printf("shouldn't term");
        exit(EXIT_FAILURE);
    }
}

int main() {
    if (thread_create(foo, 0, 0) != FAILURE) {
        printf("shouldn't create");
        exit(EXIT_FAILURE);
    }
    if (thread_join(1) != FAILURE) {
        printf("shouldn't join");
        exit(EXIT_FAILURE);
    }
    if (thread_yield() != FAILURE) {
        printf("shouldn't yield");
        exit(EXIT_FAILURE);
    }
    if (thread_libterminate() != FAILURE) {
        printf("shouldn't term\n");
        exit(EXIT_FAILURE);
    }
    if (thread_libinit(PRIORITY) == FAILURE) {
        printf("init failure\n");
        exit(EXIT_FAILURE);
    }
    if (thread_libinit(SJF) != FAILURE) {
        printf("shouldn't init again\n");
        exit(EXIT_FAILURE);
    }
    int tid;
    if ((tid = thread_create(foo, 0, 0)) == FAILURE) {
        printf("create failure");
        exit(EXIT_FAILURE);
    }
    if (thread_join(tid) == FAILURE) {
        printf("join failure");
        exit(EXIT_FAILURE);
    }
    if (thread_libterminate() == FAILURE) {
        printf("term failure\n");
        exit(EXIT_FAILURE);
    }
    printf("test passed\n");
    exit(EXIT_SUCCESS);
}
