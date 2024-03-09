/**
 * test 11 - test max threads with FIFO
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks if the library can create up to MAX_THREADS threads and stop. 
 *              
 * Expected output: 
 * 
 * !!! Before running this test, adjust MAX_THREADS to at least your design's capacity!!!
 * test 11
 * Happy Spring Break!?!    <-- 1024 times (or your setting of MAX_THREADS)
 * Max thread limit reached. Created <MAX_THREADS> threads.
 * done
*/
#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 1024 // adjust this based on your userthread design!!!

void task(void *arg) {
    printf("Happy Spring Break!?!\n");
}

int main() {
    printf("!!! Before running this test, adjust MAX_THREADS to at least your design's capacity!!!\n");

    if (thread_libinit(FIFO) == -1) {
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    }

    printf("test 11\n");

    for (int i = 1; i <= MAX_THREADS; ++i) {
        int tid = thread_create(task, NULL, 0);
        if (tid == -1) {
            printf("Max thread limit reached. Created %d threads.\n", i - 1);
            break;
        }
    }

    printf("done\n");

    if (thread_libterminate() == -1) {
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
