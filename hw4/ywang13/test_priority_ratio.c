// Author: Yuxiao Wang
// test PRIORITY ratio: print the number of finished threads by a certain point
// and the ratio of different priorities

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "userthread.h"

#define THREAD_NUM 4000
#define FAILURE -1

float count[3];
int total_count = 0;
bool stop = false;

void foo(void* arg) {
    if (stop) return;

    int num = *((int*) arg);
    int priority = (num - 1) % 3 - 1;
    count[priority + 1]++;
    if (total_count++ == THREAD_NUM / 2) {
        stop = true;
    }
}

int main(int argc, char** argv) {
    for (int i = 0; i < 3; ++i) {
        count[i] = 0;
    }

    if (thread_libinit(PRIORITY) == FAILURE) {
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
        threads[i] = thread_create(foo, num + i, i % 3 - 1);
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

    printf("hi: %.0f, mid: %.0f, lo: %.0f\n", count[0], count[1], count[2]);
    printf("hi:mid = %f, mid:low = %f\n", count[0] / count[1], count[1] / count[2]);

    exit(EXIT_SUCCESS);
}
