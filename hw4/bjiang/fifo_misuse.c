// Author: Ben Jiang
// This test is error testing for fifo
// Should not cause any memory errors or leaks when the user is not using the library correctly

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define FAIL -1
#define THREAD_NUMBER 8

void misuse(void *arg)
{
    thread_libterminate();
}

void fool(void *arg) {}

int main(void)
{
    if (thread_create(fool, NULL, 0) != FAIL)
        exit(EXIT_FAILURE);
    if (thread_create(misuse, NULL, 0) != FAIL)
        exit(EXIT_FAILURE);
    if (thread_join(3) != FAIL){
        exit(EXIT_FAILURE);
    }

    if (thread_libinit(FCFS) == FAIL)
        exit(EXIT_FAILURE);

    int tid5 = thread_create(misuse, NULL, -1); //shouldn't do anything, shouldn't be allowed 
    int tid6 = thread_create(misuse, NULL, 0); //to call threadlibterminate
    int tid7 = thread_create(misuse, NULL, 1);
    int tid8 = thread_create(misuse, NULL, 0);
    int tid1 = thread_create(fool, NULL, -1);
    int tid2 = thread_create(fool, NULL, 0);
    int tid3 = thread_create(fool, NULL, 1);
    int tid4 = thread_create(fool, NULL, 0);

    int tids[] = {tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8};
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        if (tids[i] == FAIL)
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        thread_join(tids[i]);
        
    }
    if (thread_libterminate() == FAIL)
        exit(EXIT_FAILURE);

    int tid1 = thread_create(fool, NULL, -1); //shouldn't do anything
    int tid2 = thread_create(fool, NULL, 0);
    int tid3 = thread_create(fool, NULL, 1);
    int tid4 = thread_create(fool, NULL, 0);

    exit(EXIT_SUCCESS);
}