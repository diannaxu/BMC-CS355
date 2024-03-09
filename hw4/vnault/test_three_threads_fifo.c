// Make three threads that run in infinite loops, but each wake up from sleep
// at different speeds, and yield after each loop, then put them in a
// FIFO scheduler and confirm they all alternate forever
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "userthread.h"

#define FIFO 0
#define PRIORITY 0
#define TRUE 1

void thread_fast(int myarg) {
    struct timespec thread_fast_timer;
    thread_fast_timer.tv_sec = 1;
    thread_fast_timer.tv_nsec = 0;
    while(TRUE) {
        nanosleep(&thread_fast_timer, NULL);
        printf("threadfast\n");
        thread_yield();
    }
}

void thread_slow(int myarg) {
    struct timespec thread_slow_timer;
    thread_slow_timer.tv_sec = 2;
    thread_slow_timer.tv_nsec = 0;
    while(TRUE) {
        nanosleep(&thread_slow_timer, NULL);
        printf("threadslow\n");
        thread_yield();
    }
}

void thread_slower(int myarg) {
    struct timespec thread_slow_timer;
    thread_slow_timer.tv_sec = 3;
    thread_slow_timer.tv_nsec = 0;
    while(TRUE) {
        nanosleep(&thread_slow_timer, NULL);
        printf("threadslower\n");
        thread_yield();
    }
}

int main() {
    thread_libinit(FIFO);
    int thread_slower_tid = thread_create(thread_slower, TRUE, PRIORITY);
    thread_create(thread_slow, TRUE, PRIORITY);
    thread_create(thread_fast, TRUE, PRIORITY);
    printf("Expected output: alternate between printing threadslower, threadslow, and threadfast forever\n");
    printf("Actual output:\n");
    thread_join(thread_slower_tid);
}

