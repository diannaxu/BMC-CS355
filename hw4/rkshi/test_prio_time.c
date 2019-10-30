// Author: Ruikang Shi
// test priority with interruption: create 5 threads, each sleep for 200 seconds which will be interrupted by the signal
// Output: should have no mem error and runs in order 1,2,3,4,5
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "userthread.h"

#define THREAD_NUM 5
#define SLEEP_MS 200
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    poll(NULL, 0, SLEEP_MS);
    printf("Thread %d finished\n", num);
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
        threads[i] = thread_create(foo, num + i, -1);
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

