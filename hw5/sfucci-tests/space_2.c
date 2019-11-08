#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define MEM_SIZE 4096

int main(){
  Mem_Init(MEM_SIZE);

  void * ptr1 = Mem_Alloc(2000);
  void * ptr2 = Mem_Alloc(2000);
  void * ptr3 = Mem_Alloc(96);

  Mem_Dump();
  
  if(ptr3 == NULL){
    printf("Failure\n");
    exit(EXIT_FAILURE);
  }
  printf("Success\n");
  exit(EXIT_SUCCESS);
}
