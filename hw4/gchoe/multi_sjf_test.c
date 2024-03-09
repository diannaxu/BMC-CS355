/**
 * multi_sjf_test.c
 * Author: gchoe
 * Date: 3/8/2024
 * 
 * Description:
 * Test to ensure that multiple threads are scheduled in SJF.
 * Did not add print statements for other EXIT_FAILURE's since they should
 * already be checked by the other test case files.
 *
 * Expected Result:
 * Thread 0 entered work(), working!
 *      ... (same line as above except with incrementing by one thread number)
 * Thread 9 entered work(), working!
 * Success: SJF works as expected with multiple threads!
 */

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

void work(void *arg) {
    int tid = *((int *) arg);
    printf("Thread %d entered work(), working!\n", tid);
}

int main() {
    if (thread_libinit(SJF) == -1) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++) {
        int tid = thread_create(work, &i, 0);

        if (tid == -1) {
            printf("ERROR: Could not create thread %d.\n", i);
            exit(EXIT_FAILURE);
        }

        if (thread_join(tid) == -1) {
            printf("ERROR: Could not join thread %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Success: SJF works as expected with multiple threads!\n");
    exit(EXIT_SUCCESS);
}