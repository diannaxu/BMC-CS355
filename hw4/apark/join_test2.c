#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void doThing(void* trash)
{
    printf("%s\n", (char*)trash);
}

int main()
{
    printf("thread_join() should return -1 if there are no threads to join\n");
    
    if(thread_libinit(FIFO) == 0)
    {
      printf("Thread Library successfuly created !\n");
    }else
    {
      printf("ERROR: THREAD LIBRARY CANNOT BE CREATED\n");
    }
    
    for (int i = 0; i < 8 + 1; i++)
    {
      if(thread_join(i) < 0)
      {
        printf("ERROR: Threads cannot be joined\n");
        exit(EXIT_FAILURE);
      }
    }

}