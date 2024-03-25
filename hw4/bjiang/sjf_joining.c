// Author: Ben Jiang
// Tests joining a thread that has already joined another thread and is outside of ready queue
// Should execute thread 2, 1, 3 first time, and 4, 5, 6 second time since the functions
// join threads that have already completed

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define FAIL -1

void test()
{
  thread_join(3);
  sleep(1);
  printf("In test1\n");
}

void test2()
{
  thread_join(1);
  sleep(2);
  printf("In test2\n");
}

void test3()
{
  sleep(3);
  printf("In test3\n");
}

int main(void)
{
  if (thread_libinit(SJF) == FAIL)
    exit(EXIT_FAILURE);

  int tids[3];
  
  tids[0] = thread_create(test,NULL,0);
  tids[1] = thread_create(test2,NULL,0);
  tids[2] = thread_create(test3,NULL,0);

  if (thread_join(2)==FAIL){
    exit(EXIT_FAILURE);
  }

  tids[0] = thread_create(test,NULL,0);
  tids[1] = thread_create(test2,NULL,0);
  tids[2] = thread_create(test3,NULL,0);

  if (thread_join(5)==FAIL){
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}