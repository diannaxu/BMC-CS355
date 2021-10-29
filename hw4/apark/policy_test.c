#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void doThing(void* trash)
{
    printf("%s\n", (char*)trash);
}

int main()
{
    printf("thread_libinit() should return -1 with out of bounds policy number\n");
    
    printf("\nTrying with policy number > 2\n");
    if(thread_libinit(1004) == 0)
    {
      printf("Thread Library successfuly created !\n");
    }else
    {
      printf("ERROR: THREAD LIBRARY CANNOT BE CREATED\n");
    }
    
    printf("Trying with policy number < 0\n");
    if(thread_libinit(1004) == 0)
    {
      printf("Thread Library successfuly created !\n");
    }else
    {
      printf("ERROR: THREAD LIBRARY CANNOT BE CREATED\n");
    }

}