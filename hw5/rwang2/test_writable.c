/*
 Author: Ruochun(Rachel) Wang
 Description:
 #15 test for whether allocated memory is writable
 */

 #include "mem.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>


#define INIT_SIZE 4096
#define FAILURE -1
#define NUM_ALLOC 10
int main(){
  printf("-------------- Test whether allocated memory is writable --------------\n");

  if (Mem_Init(INIT_SIZE) == FAILURE){
    printf("Initialization error\n");
    exit(EXIT_FAILURE);
  }

  long alloc_size = sizeof(int);
  for (int i = 0; i< NUM_ALLOC; i++){
    printf("Allocating interger pointer %d ...\n", i);
    int* ptr =  (int*)Mem_Alloc(alloc_size);
    if (ptr == NULL){
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
    *ptr = i;
    printf("Pointer %d is writable\n", i);

  }
  printf("Test passed!\n");


}
