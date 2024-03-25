// Author: Ben Jiang
// Tests basic fifo functionality
#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define THREAD_NUMBER 100
#define FAIL -1

void test()
{
  printf("In test1\n");
}

int main(void)
{
  if (thread_libinit(FCFS) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER];
  
  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    tids[i] = thread_create(test, NULL, 0);
  }

  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}