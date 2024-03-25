/**
 * multi_priority_test.c
 * Author: gchoe
 * Date: 3/8/2024
 * 
 * Description:
 * Basic test to ensure that two threads are scheduled in PRIORITY.
 * Did not add print statements for other EXIT_FAILURE's since they should
 * already be checked by the other test case files.
 *
 * Expected Result is printed in the order of priority so -1, 0, 1
 * So, for example:
 * Thread 1 entered work(), working!
 * Thread 4 entered work(), working!
 * Thread 7 entered work(), working!
 * Thread 2 entered work(), working!
 * Thread 5 entered work(), working!
 * Thread 8 entered work(), working!
 * Thread 3 entered work(), working!
 * Thread 6 entered work(), working!
 * Thread 9 entered work(), working!
 * Success: PRIORITY works as expected with multiple threads!
 */

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

void work(void *arg) {
    int tid = *((int *) arg);
    printf("Thread %d entered work(), working!\n", tid);
}

int main() {
    if (thread_libinit(PRIORITY) == -1) {
        exit(EXIT_FAILURE);
    }

    int priority_value = -1;

    for (int i = 1; i < 10; i++) {
        int tid = thread_create(work, &i, priority_value);
        // Allows for tid3 to have priority value -1, tid2 to be 0 and
        // tid1 to be 1
        priority_value++;

        if (priority_value > 1) {
            priority_value = -1;
        }

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

    printf("Success: PRIORITY works as expected with multiple threads!\n");
    exit(EXIT_SUCCESS);
}