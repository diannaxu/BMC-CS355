//
// Created by Sarah Depew on 3/19/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"
#include "logger.h"

#define SUCCESS 0
#define FAILURE -1
#define PRIORITY 1

void printHello () {
    printf("Hello world\n");
}

void tryYield() {
    printf("start yield\n");
    thread_yield();
    printf("end yield\n");
    printHello();
}

int main() {
    if (thread_libinit(SJF) == FAILURE)
        exit(EXIT_FAILURE);

    int tid1 = thread_create(printHello, NULL, -1);

    if (tid1 == FAILURE)
        exit(EXIT_FAILURE);

    printf("joining 1\n");
    if (thread_join(tid1) == FAILURE)
        exit(EXIT_FAILURE);

    int tid2 = thread_create(tryYield, NULL, -1);

    if (tid2 == FAILURE)
        exit(EXIT_FAILURE);

    printf("joining 2\n");
    if (thread_join(tid2) == FAILURE)
        exit(EXIT_FAILURE);

    printf("Back to main\n");

    if (thread_libterminate() == FAILURE)
        exit(EXIT_FAILURE);

    printf("Congratulations, your test was successful!\n");
    exit(EXIT_SUCCESS);
}