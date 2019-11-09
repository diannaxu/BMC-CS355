/*
 Author: Ruochun(Rachel) Wang
 Description:
 #8 test for simple allocation and free
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
  printf("-------------- simple 8-byte allocation and free--------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  void* ptr =  Mem_Alloc(ALLOC_SIZE);
  if (ptr == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  printf("\nYou should see one allocated block with size 8\n");
  Mem_Dump();

  if (Mem_Free(ptr,0) == FAILURE){
    printf("Free error\n");
    exit(EXIT_FAILURE);
  }

  printf("\nYou should see one free block with size 8\n");
  Mem_Dump();




}
