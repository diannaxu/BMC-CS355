//Author: Rachel(Ruochun) Wang
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"
void foo(void *arg){
  printf("\n");
}

int main(void) {
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);

  printf("First thread should be created successfully, second should fail\n");

  int tid1 = thread_create(foo, NULL, 1);
  int tid2 = thread_create(foo, NULL, 100);

  if (tid1 >= 0){
    printf("First thread Succeeded.\n");
  }else{
    printf("First thread Failed\n");
    exit(EXIT_FAILURE);
  }

  if (tid2 >= 0){
    printf("Second thread Succeeded.\n");
  }else{
    printf("Second thread Failed\n");
    exit(EXIT_FAILURE);
  }


  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
