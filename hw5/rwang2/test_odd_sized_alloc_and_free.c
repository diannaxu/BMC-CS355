/*
 Author: Ruochun(Rachel) Wang
 Description:
 #10 test for several odd-sized allocations and free
 */

 #include "mem.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>


#define INIT_SIZE 10000
#define ALLOC_SIZE 4
#define FAILURE -1
#define NUM_ALLOC 10
int main(){
  printf("-------------- Odd-sized allocations and free--------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }
  void* ptr_list[NUM_ALLOC];
  for (int i = 0; i< NUM_ALLOC; i++){
    void* ptr =  Mem_Alloc(ALLOC_SIZE * (i+1) + 3);
    if (ptr == NULL){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
    ptr_list[i] = ptr;
    printf("Current allocation size: %d\n", ALLOC_SIZE * (i+1)+3);
  }

  for (int i = 0; i< NUM_ALLOC; i++){
    if ( Mem_Free(ptr_list[i], 0) == FAILURE){
      printf("Free error\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("You should see %d fred blocks with size of multiples of 8\n", NUM_ALLOC);
  Mem_Dump();

}
