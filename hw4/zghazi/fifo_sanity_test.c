
/* Author: Zaynab Ghazi */
/*
Expected output:
Thread prints 1
Thread prints 2
Thread prints 2
Thread prints 3
Thread prints 3
Thread prints 3
Thread prints 4
Thread prints 4
Thread prints 4
Thread prints 5
Thread prints 5
Thread prints 5
Thread prints 6
Thread prints 6
Thread prints 6
Thread prints 7
Thread prints 7
Thread prints 7
Thread prints 8
Thread prints 8
Thread prints 8
Thread prints 9
Thread prints 9
Thread prints 9
Thread prints 10
Thread prints 10
Thread prints 10
Thread prints 4
Thread prints 5
Thread prints 5
Thread prints 6
Thread prints 6
Thread prints 6
Thread prints 7
Thread prints 7
Thread prints 7
Thread prints 7
Thread prints 8
Thread prints 8
Thread prints 8
Thread prints 8
Thread prints 8
Thread prints 9
Thread prints 9
Thread prints 9
Thread prints 9
Thread prints 9
Thread prints 9
Thread prints 10
Thread prints 10
Thread prints 10
Thread prints 10
Thread prints 10
Thread prints 10
Thread prints 10
*/
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void test(void *arg)
{
  int i = *(int *)arg;
for(int j=0; j<i;j++){
  if (j==3) thread_yield();
  printf("Thread prints %d\n",i);
}  
}

int main()
{
  if (thread_libinit(FIFO) == -1)
  {
    printf("Error initializing library!\n");
    exit(EXIT_FAILURE);
  }
  int thread_ids[10];
  int values[10];
  for (int i = 0; i < 10; i++)
  {
    values[i] = i + 1;
    thread_ids[i] = thread_create(test, &values[i], 0);
    if (thread_ids[i] == -1)
    {
      printf("Error creating thread!\n");
      exit(EXIT_FAILURE);
    }
  }
  for (int i = 0; i < 10; i++){
     if (thread_join(thread_ids[i])==-1)
    {
      printf("Error joining thread!\n");
      exit(EXIT_FAILURE);
    }
  } 
  printf("program end\n");
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);
 exit(EXIT_SUCCESS);
}
