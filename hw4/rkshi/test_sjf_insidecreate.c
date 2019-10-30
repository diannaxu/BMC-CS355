// Author: Ruikang
// test SJF with thread created by other thread: first create 10 threads each with default estimation of runtime, then
// each thread will create a new thread; since the main thread has done join operation, those new threads
// will have a much smaller estimation of runtime than the default one, which makes them finished first.
// order of printing "Thread n finished" with 11,1,12,2...20,10

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "userthread.h"

#define THREAD_NUM 10
#define SLEEP_MS 10
#define FAILURE -1

void foo2(void* arg){
    int num = *((int*) arg);
    printf("Thread %d finshed\n", num);
}

void foo(void* arg) {
    int num = *((int*) arg);
    int tid;
    int num2 = num+10;
    int* k = &num2;
    tid = thread_create(foo2, k, 0);
    thread_join(tid);
    printf("Thread %d finished\n", num);
}


int main(int argc, char** argv) {
    if (thread_libinit(SJF) == FAILURE) {
        printf("init failure\n");
        exit(EXIT_FAILURE);
    }

    // thread #
    int num[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM*2; ++i) {
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
