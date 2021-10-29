#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"
#ifndef NULL
#define NULL (0)
#endif


void best(void* args)
{
    printf("im the best :D\n");
}

void average(void* args)
{
    printf("im so-so :>\n");
}
void worst(void* args)
{
    printf("im the worst D:\n");
}
/*
  a very simple basic sjf test.
  See whether sjf's priority queue works as expected.
*/

int main() {

  if(thread_libinit(PRIORITY) == 0)
  {
    printf("Thread Library successfuly created !\n");
  }else
  {
    printf("ERROR: THREAD LIBRARY CANNOT BE CREATED\n");
  }
  
  printf("Logger should show that thread 1 executes first\n");
  int one =  thread_create(best,NULL,-1);
  int two =  thread_create(average,NULL,0);
  int three = thread_create(worst, NULL, 1);


  if(thread_join(one) < 0)
  {
    exit(EXIT_FAILURE);
  }
  if(thread_join(two) < 0)
  {
    exit(EXIT_FAILURE);
  }
  if(thread_join(three) < 0)
  {
    exit(EXIT_FAILURE);
  }

  if(thread_libterminate() == 0)
  {
    printf("Thread Library is gone !\n");
  }else
  {
    printf("ERROR: CANNOT DELETE THREAD LIBRARY\n");
  }
  return 0;

}