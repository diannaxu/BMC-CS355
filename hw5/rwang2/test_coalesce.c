/*
 Author: Ruochun(Rachel) Wang
 Description:
 #7 test for coalesce
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
  printf("--------------- Test Coalesce --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }
  void* ptr_list[NUM_ALLOC];
  for (int i = 0; i< NUM_ALLOC; i++){
    void* ptr =  Mem_Alloc(ALLOC_SIZE * (i+1));
    if (ptr == NULL){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
    ptr_list[i] = ptr;
    //printf("Current allocation size: %d\n", ALLOC_SIZE * (i+1));
  }


  for (int i = 0; i< NUM_ALLOC; i++){
    if ( i%2 == 0 && Mem_Free(ptr_list[i], 0) == FAILURE){
      printf("Free error\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("You should see alternative free and allocated blocks\n");
  Mem_Dump();

  printf("\n----- Test for local coalesce\n");
  int mid = NUM_ALLOC / 2;
  if (Mem_Free(ptr_list[mid], 2) == FAILURE){
    printf("Free error\n");
    exit(EXIT_FAILURE);
  }
  printf("You should see middle block get merged\n");
  Mem_Dump();

  printf("\n----- Test for global coalesce\n");
  for (int i = 0; i< NUM_ALLOC; i++){
    if ( i%2 == 1 && i != mid &&  Mem_Free(ptr_list[i], 1) == FAILURE){
      printf("Free error\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("You should see one merged free block\n");
  Mem_Dump();

}
