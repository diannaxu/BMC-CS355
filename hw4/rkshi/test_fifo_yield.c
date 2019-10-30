// Author: Ruikang Shi
// test FIFO yield: create threads 1, 2,...,10; the even number threads yield
// order of printing "Thread n finished" should be 1,3,5,7,9,2,4,6,8,10

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 10
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    if (num % 2 == 0) {
        thread_yield();
    }

    printf("Thread %d finished \n", num);
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
