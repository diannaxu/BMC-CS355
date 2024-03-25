// Make a thread that runs in an infinite loop, but yields after each loop,
// then put it in a SJF scheduler alone and confirm it always runs
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "userthread.h"

#define SJF 1
#define PRIORITY 0
#define TRUE 1

void thread_one(int myarg) {
    struct timespec thread_one_timer;
    thread_one_timer.tv_sec = 1;
    thread_one_timer.tv_nsec = 0;
    while(TRUE) {
        nanosleep(&thread_one_timer, NULL);
        printf("threadone\n");
        thread_yield();
    }
}

int main() {
    thread_libinit(SJF);
    int thread_one_tid = thread_create(thread_one, TRUE, PRIORITY);
    printf("Expected output: print 'threadone' every second forever\n");
    printf("Actual output:\n");
    thread_join(thread_one_tid);
}

