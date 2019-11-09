/*
 Author: Ruochun(Rachel) Wang
 Description:
 #5 Test bad arguments to Mem_init
 */

 #include "mem.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>


#define INIT_SIZE 4096
#define ALLOC_SIZE 1
#define FAILURE -1
int main(){
  printf("-------------- Test bad arguments to Mem_Init --------------\n");

  printf("Try negative size\n");
  if (Mem_Init(-1) == FAILURE){
    printf("First Test passed\n");
  }else{
    printf("Test failed\n");
  }

  printf("Try double init\n");
  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization Error\n");
  }else{
    if (Mem_Init(INIT_SIZE) == FAILURE){
      printf("Second Test passed\n");
    }else{
      printf("Test failed\n");
    }
  }
}
