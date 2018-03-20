#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define N 2
#define FAIL -1

void thirdlayer(void *arg)
{
  thread_yield();
}

void secondlayer(void *arg)
{
  int tid;
  for (int i = 0; i < N; i++)
  {
    tid = thread_create(thirdlayer, NULL, 1);
    if (tid == FAIL)
      exit(EXIT_FAILURE);
    if (thread_join(tid) == FAIL)
      exit(EXIT_FAILURE);
  }
}

void firstlayer(void *arg)
{
  int tid;
  for (int i = 0; i < N; i++)
  {
    tid = thread_create(secondlayer, NULL, 1);
    if (tid == FAIL)
      exit(EXIT_FAILURE);
    if (thread_join(tid) == FAIL)
      exit(EXIT_FAILURE);
  }
}

void wisefool(void *arg)
{
  printf("%s\n", arg);
}

int main(void)
{
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int t = thread_create(firstlayer, NULL, 1);
  printf("* A double nested test case for FIFO scheduling policy.\n");
  printf("* The threads should finish in the following order.\n");
  if (thread_join(t) == FAIL)
    exit(EXIT_FAILURE);

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}