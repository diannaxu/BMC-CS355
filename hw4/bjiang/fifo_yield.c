// Author: Ben Jiang
// This tests yield for FIFO, should see some jobs scheduled and immediately stopped, and then rescheduled
// Shouldn't cause any memory leaks or errors

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define THREAD_NUMBER 10
#define FAIL -1

void fool(void *arg)
{
  printf("%s\n", arg);
}

void fool2(void *arg)
{
    thread_yield();
    printf("%s\n", arg);
}

int main(void)
{
  if (thread_libinit(FCFS) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER];
  char os_string[] = "I love OS";
  
  for (int i = 0; i < THREAD_NUMBER; i+=2)
  {
    tids[i] = thread_create(fool, os_string, 0);
    tids[i + 1] = thread_create(fool2,os_string,0);
  }

  for (int i = 0; i < THREAD_NUMBER - 1; i++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
