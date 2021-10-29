#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void doThing(void* trash)
{
    printf("%s\n", (char*)trash);
}

int main()
{
    printf("thread_libterminate() should return -1 if there is no thread library to terminate\n");

    if(thread_libterminate() == 0)
    {
      printf("Thread Library is gone !\n");
    }else
    {
      printf("ERROR: CANNOT DELETE THREAD LIBRARY\n");
      exit(EXIT_FAILURE);
    }

}