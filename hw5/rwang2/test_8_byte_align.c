/*
 Author: Ruochun(Rachel) Wang
 Description:
 #1 check for 8-byte alignment
 */

 #include "mem.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>


#define INIT_SIZE 4096
#define ALLOC_SIZE 1
#define FAILURE -1
int main(){
  printf("-------------- 8-byte alignment --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  void* ptr =  Mem_Alloc(ALLOC_SIZE);
  if (ptr == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  if (((long) ptr) % 8 != 0){
    printf("Test failed, allocation is not 8-byte aligned.\n");
  }else{
    printf("Test passed for 8-byte alignment.\n");
  }

}
