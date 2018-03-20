#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAIL -1

void highest(void *arg)
{
    printf("This thread's priority is highest, -1.\n");
}

void second(void *arg)
{
    printf("This thread's priority is second priority, 0.\n");
}

void lowest(void *arg)
{
    printf("This thread's priority is lowest, 1.\n");
}

int main(void)
{
    if (thread_libinit(PRIORITY) == FAIL)
        exit(EXIT_FAILURE);
    int tid1 = thread_create(highest, NULL, -1);
    int tid2 = thread_create(second, NULL, 0);
    int tid3 = thread_create(lowest, NULL, 1);
    int tid4 = thread_create(second, NULL, 0);
    int tid5 = thread_create(highest, NULL, -1);
    int tid6 = thread_create(highest, NULL, -1);
    int tid7 = thread_create(second, NULL, 0);
    int tid8 = thread_create(highest, NULL, -1);
    int tid9 = thread_create(lowest, NULL, 1);

    printf("* A simple test case for PRIORITY scheduling policy.\n");
    printf("* Testing only thread_create and thread_join.\n");
    int num = 9;
    int tids[] = {tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9};
    for (int i = 0; i < num; i++)
    {
        if (tids[i] == FAIL)
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num; i++)
    {
        if (thread_join(tids[i]) == FAIL)
            exit(EXIT_FAILURE);
    }
    if (thread_libterminate() == FAIL)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}