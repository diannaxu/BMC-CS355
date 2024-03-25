/**
 * yield_sjf_test.c
 * Author: gchoe
 * Date: 3/8/2024
 * 
 * Description:
 * Basic test to ensure that thread_yield works in SJF.
 * Did not add print statements for other EXIT_FAILURE's since they should
 * already be checked by the other test case files.
 *
 * Expected Result:
 * Thread 1 entered work(), working!
 * Thread 2 entered work(), working!
 * Thread 1 finished work().
 * Thread 2 finished work().
 * Success: SJF with yield works as expected!
 */

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

void work(void *arg) {
    int tid = *((int *) arg);
    printf("Thread %d entered work(), working!\n", tid);
    thread_yield();
    printf("Thread %d finished work().\n", tid);
}

int main() {
    if (thread_libinit(SJF) == -1) {
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < 3; i++) {
        int tid = thread_create(work, &i, 0);

        if (tid == -1) {
            exit(EXIT_FAILURE);
        }

        if (thread_join(tid) == -1) {
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Success: SJF with yield works as expected!\n");
    exit(EXIT_SUCCESS);
}