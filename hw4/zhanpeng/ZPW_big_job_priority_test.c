#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

#define FAIL -1

void big(void *arg)
{
    poll(NULL, 0, 200);
}

int main(void)
{
    if (thread_libinit(PRIORITY) == FAIL)
        exit(EXIT_FAILURE);
    int tid1 = thread_create(big, NULL, -1);
    int tid2 = thread_create(big, NULL, 0);
    int tid3 = thread_create(big, NULL, 1);
    int tid4 = thread_create(big, NULL, -1);
    int tid5 = thread_create(big, NULL, 0);
    int tid6 = thread_create(big, NULL, 1);

    printf("* A intense test case for PRIORITY scheduling policy handling a big job.\n");
    printf("* Testing thread_create, thread_join and sigalarm working or not.\n");
    printf("* You should see threads ending from highest to lowest and yielding for running too long.\n");
    int num = 6;
    int tids[] = {tid1, tid2, tid3, tid4, tid5, tid6};
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