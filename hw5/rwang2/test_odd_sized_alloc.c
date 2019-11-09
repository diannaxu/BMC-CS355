/*
 Author: Ruochun(Rachel) Wang
 Description:
 #4 test for several odd-sized allocations
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
  printf("-------------- Odd-sized allocations --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i< NUM_ALLOC; i++){
    void* ptr =  Mem_Alloc(ALLOC_SIZE * (i+1) + 3);
    if (ptr == NULL){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
    printf("Current allocation size: %d\n", ALLOC_SIZE * (i+1)+3);
  }

  Mem_Dump();
  printf("You should see %d allocated blocks with size of multiples of 8\n", NUM_ALLOC);


}
