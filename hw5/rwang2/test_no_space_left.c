/*
 Author: Ruochun(Rachel) Wang
 Description:
 #13 test when there is no space left to allocate
 */

 #include "mem.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>


#define INIT_SIZE 4000
#define ALLOC_SIZE 8
#define FAILURE -1
#define NUM_ALLOC 10
int main(){
  printf("--------------- Test when there is no space left to allocate --------------\n");


  printf("\nInitialize with size 4000...\n");
  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }
  printf("\nAllocating size 900...\n");
  void* ptr1 =  Mem_Alloc(900);
  if (ptr1 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  printf("\nAllocating size 2000...\n");

  void* ptr2 =  Mem_Alloc(2000);
  if (ptr2 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  printf("\nAllocating size 900...\n");
  void* ptr3 =  Mem_Alloc(900);
  if (ptr3 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }


  printf("\nAllocating size 1000... and this one should fail\n");
  void* ptr4 =  Mem_Alloc(1000);
  if (ptr4 == NULL){
    printf("Test passed!\n");
  }else{
    printf("Test failed\n");
  }

}
