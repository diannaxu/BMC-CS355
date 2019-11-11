/*
 Author: Ruochun(Rachel) Wang
 Description:
 #6 test worst fit allocation
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
  printf("--------------- Test worst fit allocation --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  void* ptr1 =  Mem_Alloc(900);
  if (ptr1 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  void* ptr2 =  Mem_Alloc(2000);
  if (ptr2 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }


  void* ptr3 =  Mem_Alloc(900);
  if (ptr3 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }


  if (Mem_Free(ptr1,0) == FAILURE){
    printf("Free error\n");
    exit(EXIT_FAILURE);
  }

  if (Mem_Free(ptr2,0) == FAILURE){
    printf("Free error\n");
    exit(EXIT_FAILURE);
  }

  if (Mem_Free(ptr3,0) == FAILURE){
    printf("Free error\n");
    exit(EXIT_FAILURE);
  }

  //Mem_Dump();

  void* ptr4 =  Mem_Alloc(500);
  if (ptr4 == NULL){
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  printf("You should see the second block get allocated\n");
  Mem_Dump();


}
