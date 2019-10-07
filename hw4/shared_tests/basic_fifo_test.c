// Author: Zhanpeng Wang

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUMBER 100
#define FAIL -1

void wisefool(void *arg)
{
  printf("%s\n", arg);
}

int main(void)
{
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER];
  char os_string[] = "OS is hard!";
  
  printf("* A simple test case for FIFO scheduling policy.\n");
  printf("* It should print \"OS is hard!\" for all %i threads if success.\n", THREAD_NUMBER);
  printf("* All %i threads should be scheduled and finished in order. Check the log file for full detail.\n", THREAD_NUMBER);
  
  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    tids[i] = thread_create(wisefool, os_string, 0);
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