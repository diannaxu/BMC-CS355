#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define MEM_SIZE 4096


/*

This tests the worst case with memory allocation,
in which the user requests MEMSIZE 1-byte blocks.
All of these requests should be granted.
*/

int main(){
  Mem_Init(MEM_SIZE);

  void * ptr1 = Mem_Alloc(2000);
  void * ptr2 = Mem_Alloc(2000);
  void * ptr3 = Mem_Alloc(2000);

  //  Mem_Dump();

  if(ptr1 == NULL || ptr2 == NULL){
    printf("Failure: should be able to allocate two pointers of size %ld\n",2000);
    exit(EXIT_FAILURE);
  }
  if(ptr3 != NULL){
    printf("Failure: should not be space for element of size %ld\n", 2000);
    exit(EXIT_FAILURE);
  }
  Mem_Free(ptr2,1);

  //  Mem_Dump();

  if((ptr3 = Mem_Alloc(2097)) != NULL){
    printf("Failure: should not be space for element of size %ld\n",2097);
    exit(EXIT_FAILURE);
  }
  if((ptr3 = Mem_Alloc(2096)) == NULL){
    printf("Failure: should be space for element of size %ld\n", 2096);
    exit(EXIT_FAILURE);
  }
    
  printf("Success\n");
  exit(EXIT_SUCCESS);
}
