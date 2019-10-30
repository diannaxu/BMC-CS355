// Author: Ruikang Shi
// test SJF basic: 10 threads in total, each thread will first sleep for some time and then yield before finished
// larger tid threads have less sleep time thus should finish earlier.
// order of printing "Thread n sleep" with n from 1 to 10 and then "Thread n finished" with n from 10 to 1

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "userthread.h"

#define THREAD_NUM 10
#define SLEEP_MS 100
#define FAILURE -1

void foo(void* arg) {
    int num = *((int*) arg);
    printf("Thread %d sleep\n",num);
    poll(NULL, 0, SLEEP_MS*(11-num));
    thread_yield();
    printf("Thread %d finished\n", num);
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
        }else{
            printf("create success %d\n", threads[i]);
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
