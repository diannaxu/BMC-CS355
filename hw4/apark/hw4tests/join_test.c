#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void doThing(void* trash)
{
    printf("%s\n", (char*)trash);
}

int main()
{
    printf("thread_join() should return -1 if the thread library is not initialized\n");
    
    for (int i = 0; i < 8 + 1; i++)
    {
      if(thread_join(i) < 0)
      {
        printf("ERROR: Threads cannot be joined");
        exit(EXIT_FAILURE);
      }
    }

}