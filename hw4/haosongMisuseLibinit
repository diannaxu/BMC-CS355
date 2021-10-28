// Author: Haosong Huang

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAIL -1
#define THREAD_NUMBER 8

void misuse(void *arg)
{
    thread_libterminate();
    printf("The thread_libterminate misuse. Shouldn't do anything weird\n");
}

void fool(void *arg) {}

int main(void)
{
    printf(" * Testing a simple FIFO with misuse of the userthread library\n.");
    printf(" * Shouldn't have segfault or memory leak. \n");
    if (thread_create(fool, NULL, 0) != FAIL)
        exit(EXIT_FAILURE);
    if (thread_create(misuse, NULL, 0) != FAIL)
        exit(EXIT_FAILURE);
    
    // Allow to call multiple libinit
    if (thread_libinit(FIFO) == FAIL)
        exit(EXIT_FAILURE);
    if (thread_libinit(SJF) == FAIL)
        exit(EXIT_FAILURE);
    if (thread_libinit(FIFO) == FAIL)
        exit(EXIT_FAILURE);
    int tid1 = thread_create(fool, NULL, -1);
    int tid2 = thread_create(fool, NULL, 0);
    int tid3 = thread_create(fool, NULL, 1);
    int tid4 = thread_create(fool, NULL, 0);
    int tid5 = thread_create(misuse, NULL, -1);
    int tid6 = thread_create(misuse, NULL, 0);
    int tid7 = thread_create(misuse, NULL, 1);
    int tid8 = thread_create(misuse, NULL, 0);

    int tids[] = {tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8};
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        if (tids[i] == FAIL)
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        if (thread_join(tids[i]) == FAIL)
            exit(EXIT_FAILURE);
    }
    if (thread_libterminate() == FAIL)
        exit(EXIT_FAILURE);

    thread_join(21938475); // shouldn't do anything
    thread_join(10293847);
    exit(EXIT_SUCCESS);
}
