/*
 Author: Ruochun(Rachel) Wang
 Description:
 #2 test for simple 8-byte allocation
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
  printf("-------------- simple 8-byte allocation --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i< NUM_ALLOC; i++){
    void* ptr =  Mem_Alloc(ALLOC_SIZE);
    if (ptr == NULL){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
  }

  Mem_Dump();
  printf("You should see %d allocated blocks with size 8\n", NUM_ALLOC);


}
