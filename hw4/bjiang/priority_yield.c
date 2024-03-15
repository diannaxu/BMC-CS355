// Author: Ben Jiang
// This tests yield for SJF, should see some jobs scheduled and immediately stopped, and then rescheduled
// Shouldn't cause any memory leaks or errors

#include <stdio.h>
#include <stdlib.h>
#include "../userthread.h"

#define THREAD_NUMBER 10
#define FAIL -1

struct timespec ts1,ts2,ts3;


void fool()
{
    nanosleep(&ts1,NULL);
    printf("Test1\n");
}

void fool2()
{
    thread_yield();
    nanosleep(&ts2,NULL);
    printf("Test2\n");
}

void fool3()
{
    thread_yield();
    nanosleep(&ts3,NULL);
    printf("Test3\n");
}

void fool4()
{
    nanosleep(&ts2,NULL);
    printf("Test4\n");
}

int main(void)
{
    ts1.tv_nsec = 10000;
    ts1.tv_sec = 0;
    ts2.tv_nsec = 20000;
    ts2.tv_sec = 0;
    ts3.tv_nsec = 30000;
    ts3.tv_sec = 0;

  if (thread_libinit(PRIORITY) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER * 4];
  

  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    tids[4*i] = thread_create(fool, NULL, HIGHPRIORITY);
    tids[4*i + 1] = thread_create(fool2,NULL,MIDPRIORITY);
    tids[4*i + 2] = thread_create(fool3,NULL,LOWPRIORITY);
    tids[4*i + 3] = thread_create(fool4,NULL,HIGHPRIORITY);
  }
  
  for (int i = 0; i < THREAD_NUMBER*4; i++)
  {
    if (thread_join(tids[i]) == FAIL){
       exit(EXIT_FAILURE);
    }
  }


  if (thread_libterminate() == FAIL){
    exit(EXIT_FAILURE);
  }
  printf("Terminated\n");

  exit(EXIT_SUCCESS);
}
