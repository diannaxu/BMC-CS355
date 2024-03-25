#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define MAX_THREADS 64

void thread_func(void *arg) {
    printf("Thread %d running\n", *(int *)arg);
}

int main() {
    int i;

    // Test case 1: Invalid scheduling policy
    int ret = thread_libinit(42);
    if (ret != -1) {
        printf("Test case 1 failed: Expected -1, got %d\n", ret);
        exit(1);
    }
    printf("Test case 1 passed\n");

    // Test case 2: Exceeding maximum number of threads
    ret = thread_libinit(FIFO);
    if (ret != 0) {
        printf("Test case 2 failed: Expected 0, got %d\n", ret);
        exit(1);
    }
    int tids[MAX_THREADS];
    for (i = 0; i < MAX_THREADS-1; i++) {
        tids[i] = thread_create(thread_func, &i, 0);
        if (tids[i] == -1) {
            printf("Test case 2 failed: Thread creation failed before reaching maximum limit\n");
            exit(1);
        }
    }
    int tid = thread_create(thread_func, &i, 0);
    if (tid == -1) {
        printf("Test case 2 passed\n");
    } else {
        printf("Test case 2 failed: Thread creation succeeded after reaching maximum limit\n");
        exit(1);
    }
    
    // Terminate the thread library after test case 2
    ret = thread_libterminate();
    if (ret != 0) {
        printf("Thread library termination failed\n");
        exit(1);
    }
    
    // Test case 3: Joining a non-existent thread
    ret = thread_libinit(FIFO);
    if (ret != 0) {
        printf("Test case 3 failed: Expected 0, got %d\n", ret);
        exit(1);
    }
    ret = thread_join(-1);
    if (ret != -1) {
        printf("Test case 3 failed: Expected -1, got %d\n", ret);
        exit(1);
    }
    printf("Test case 3 passed\n");

    // Test case 4: Joining a terminated thread
    ret = thread_libinit(FIFO);
    if (ret != 0) {
        printf("Test case 4 failed: Expected 0, got %d\n", ret);
        exit(1);
    }
    tid = thread_create(thread_func, &tid, 0);
    if (tid == -1) {
        printf("Test case 4 failed: Thread creation failed\n");
        exit(1);
    }
    ret = thread_join(tid);
    if (ret != 0) {
        printf("Test case 4 failed: Expected 0, got %d\n", ret);
        exit(1);
    }
    ret = thread_join(tid);
    if (ret != 1) {
        printf("Test case 4 failed: Expected 1, got %d\n", ret);
        exit(1);
    }
    printf("Test case 4 passed\n");

    // Terminate the thread library after test case 4
    ret = thread_libterminate();
    if (ret != 0) {
        printf("Thread library termination failed\n");
        exit(1);
    }

    // Test case 5: Library termination
    ret = thread_libinit(FIFO);
    if (ret != 0) {
        printf("Test case 5 failed: Expected 0, got %d\n", ret);
        exit(1);
    }
    ret = thread_libterminate();
    if (ret != 0) {
        printf("Test case 5 failed: Expected 0, got %d\n", ret);
        exit(1);
    }
    printf("Test case 5 passed\n");

    printf("All test cases passed\n");
    return 0;
}