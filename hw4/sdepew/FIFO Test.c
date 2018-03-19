#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define SUCCESS 0
#define FAILURE -1
#define PRIORITY 1

void printHello() {
    printf("Hello World\n");
}

/*
 * Simple FIFO test with main's functionality as a thread is tested.
 */
int main(void) {
    if (thread_libinit(FIFO) == FAILURE)
        exit(EXIT_FAILURE);

    printf("This is a FIFO test where main is tested as a thread.\n");

    int tid1 = thread_create(printHello, NULL, PRIORITY);
    if (thread_join(tid1) == FAILURE)
        exit(EXIT_FAILURE);

    printf("Back in Main\n");

    int tid2 = thread_create(printHello, NULL, PRIORITY);
    if (thread_join(tid2) == FAILURE)
        exit(EXIT_FAILURE);

    printf("Should run main->%d->%d and print Hello World, Back in Main, and Hello World if successful.\n", tid1, tid2);

    if (thread_libterminate() == FAILURE)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}