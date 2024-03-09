/**
 * max_thread_test.c
 * Author: gchoe
 * Date: 3/8/2024
 * 
 * Description:
 * Basic test to ensure that MAX_THREADS limit is not surpassed (FIFO).
 * Did not add print statements for other EXIT_FAILURE's since they should
 * already be checked by the other test case files.
 *
 * Expected Result:
 * Thread 1 entered work(), working!
 *      ... (same line as above except with incrementing by one thread number)
 * Thread [MAX_THREADS VALUE HERE] entered work(), working!
 * Success: MAX_THREADS reached works as expected!
 */

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define MAX_THREADS 100

void work(void *arg) {
    int tid = *((int *) arg);
    printf("Thread %d entered work(), working!\n", tid);
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= MAX_THREADS; i++) {
        int tid = thread_create(work, &i, 0);

        if (tid == -1) {
            exit(EXIT_FAILURE);
        }

        if (thread_join(tid) == -1) {
            exit(EXIT_FAILURE);
        }
    }

    // Attempting to create one more thread above MAX_THREADS limit
    int extra = (int)(MAX_THREADS + 1);
    int extra_tid = thread_create(work, &extra, 0);

    if (tid != -1) {
        printf("ERROR: Maximum number of threads reached, yet new thread is" +
            " made.\n");
        exit(EXIT_FAILURE);
    }

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Success: MAX_THREADS reached works as expected!\n");
    exit(EXIT_SUCCESS);
}