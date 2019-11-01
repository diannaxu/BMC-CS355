//Author: Rachel(Ruochun) Wang
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

char string[] = "Blablabla!";
void foo(void *arg)
{
  printf("%s\n", (char*)arg);
}

int main(void)
{
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);

  int tids[10];

  printf("Should print %s 10 times.\n", string);

  for (int i = 0; i < 10; i++)
  {
    tids[i] = thread_create(foo, string, 0);
  }

  for (int i = 0; i < 10; i++)
  {
    if (thread_join(tids[i]) == -1){
      exit(EXIT_FAILURE);
    }
  }

  if (thread_libterminate() == -1){
    exit(EXIT_FAILURE);
  }


  exit(EXIT_SUCCESS);
}
