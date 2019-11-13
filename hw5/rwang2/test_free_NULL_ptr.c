/*
 Author: Ruochun(Rachel) Wang
 Description:
 #14 test for freeing a NULL pointer
 */

 #include "mem.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>


#define INIT_SIZE 10000
#define ALLOC_SIZE 8
#define FAILURE -1
#define NUM_ALLOC 10
int main(){
  printf("--------------- Test Freeing a NULL Pointer --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }
  if (Mem_Free(NULL,0) == FAILURE){
    printf("Test passed, caught error when freeing a NULL pointer\n");
  }else{
    printf("Test failed, did not catch the error when pointer is NULL\n");
  }

}
