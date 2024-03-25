// Author: Ben Jiang

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define THREAD_NUMBER 2
#define FAIL -1

void test(void *arg)
{
  sleep(1);
}

void test1(void *arg)
{
  sleep(2);
}

void test2(void *arg)
{
  sleep(3);
}

int main(void)
{
  if (thread_libinit(SJF) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER*3];
  char os_string[] = "OS is hard!";
  
  printf("* A simple test case for SJF scheduling policy.\n");
  printf("* It should schedule jobs in a correct order for all %i*3 threads if success.\n", THREAD_NUMBER);
   
  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    tids[i*3] = thread_create(test, NULL, 0);
    tids[i*3+1] = thread_create(test1,NULL,0);
    tids[i*3+2] = thread_create(test2,NULL,0);
  }

  for (int i = 0; i < THREAD_NUMBER*3; i++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    tids[i*3] = thread_create(test2, NULL, 0);
    tids[i*3+1] = thread_create(test1,NULL,0);
    tids[i*3+2] = thread_create(test,NULL,0);
  }

  for (int i = 0; i < THREAD_NUMBER*3; i++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);

}
