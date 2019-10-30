// Author: Ruikang Shi
// test FIFO basic: test basic init create join and then term.
// order of printing "create thread: n" with n from 1 to 10 and then "Thread n finished" with n from 1 to 10

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 10
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    printf("Thread %d finished\n", num);
}

int main(int argc, char** argv) {
    if (thread_libinit(FIFO) == FAILURE) {
        printf("init failure\n");
        exit(EXIT_FAILURE);
    }else{
        printf("init success\n");
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
        }else{
            printf("create thread: %d\n", threads[i]);
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
    }else{
        printf("term success\n");
    }

    exit(EXIT_SUCCESS);
}
