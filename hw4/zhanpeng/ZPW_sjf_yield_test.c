#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

#define N 5
#define FAIL -1

void wisefool50(void *args) {
  for (int i = 0; i < N; i++) {
    poll(NULL, 0, 50);
    thread_yield();
  }
}

void wisefool300(void *args) {
  for (int i = 0; i < N; i++) {
    poll(NULL, 0, 300);
    thread_yield();
  }
}

int main(void)
{
    if (thread_libinit(SJF) == FAIL)
        exit(EXIT_FAILURE);
    int tid1 = thread_create(wisefool50, NULL, 0);
    int tid2 = thread_create(wisefool300, NULL, 0);
    int tid3 = thread_create(wisefool50, NULL, 0);
    int tid4 = thread_create(wisefool300, NULL, 0);

    printf("* A intense test case for SJF scheduling policy running a big job.\n");
    printf("* Thread %d, Thread %d will end earlier than Thread %d, Thread %d -> %d.\n", tid1, tid3, tid2, tid4);
    int num = 4;
    int tids[] = {tid1, tid2, tid3, tid4};
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