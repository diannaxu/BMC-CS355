#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void doThing(void* trash)
{
    printf("%s\n", (char*)trash);
}

int main()
{
    if(thread_libinit(FIFO) == 0)
    {
      printf("Thread Library successfuly created !\n");
    }else
    {
      printf("ERROR: THREAD LIBRARY CANNOT BE CREATED\n");
      exit(EXIT_FAILURE);
    }

    printf("Logger should show threads in FIFO order and on program print hello 1- times \n");
    void *arg = "hello";
    int create = 0;
    for (int i = 0; i < 10; i++)
    {
      create = thread_create(doThing, arg, -1);
    }
    for (int i = 0; i < create + 1; i++)
    {
      if(thread_join(i) < 0)
      {
        exit(EXIT_FAILURE);
      }
    }

    if(thread_libterminate() == 0)
    {
      printf("Thread Library is gone !\n");
    }else
    {
    printf("ERROR: CANNOT DELETE THREAD LIBRARY\n");
    }

}
