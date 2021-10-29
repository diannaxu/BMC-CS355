#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void doThing(void* trash)
{
    printf("%s\n", (char*)trash);
}

int main()
{
    printf("thread_create() should return -1 if thread library has not been initialized\n");
    void *arg = "hello";
    int create = 0;
    for (int i = 0; i < 10; i++)
    {
      create = thread_create(doThing, arg, -1);
      if (create < 0)
      {
          printf("ERROR: Thread cannot be created\n");
          exit(EXIT_FAILURE);
      }
    }
}