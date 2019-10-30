// Author: Ruikang Shi
// test priority basic: create 30 threads, first 10 has priority -1, the next 10 has 0, and the last 10 has 1
// Output: Success run 30 threads, with bigger number threads more likely to end later
#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 30
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    printf("Thread %d running\n", num);
}

int main(int argc, char** argv) {
    if (thread_libinit(PRIORITY) == FAILURE) {
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
        threads[i] = thread_create(foo, num + i, (i /10)-1);
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

