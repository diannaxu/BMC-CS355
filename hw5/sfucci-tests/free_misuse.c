#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define MEM_SIZE 4096

int main(){
  Mem_Init(MEM_SIZE);

  if(Mem_Free(NULL,0)!= -1){
    printf("Fail: Cannot free a null pointer\n");
    exit(EXIT_FAILURE);
  }

  if(Mem_Free(NULL,1) == -1){
    printf("Fail: Mem_Free(NULL, 1) is a valid call\n");
    exit(EXIT_FAILURE);
  }
  if(Mem_Free(NULL,2) != -1){
    printf("Fail: Mem_Free(NULL, 2) is misuse\n");
    exit(EXIT_FAILURE);
  }
  if(Mem_Free(0,0) != -1){
    printf("Fail: this is recipe for disaster. This should honestly probably seg fault if you don't handle this, and this print statement shouldn't run unless you return some failure code other than -1\n");
    exit(EXIT_FAILURE);
  }

  void * ptr = Mem_Alloc(10);
  Mem_Free(ptr, 0);

  if(Mem_Free(ptr,0) == 0){
    printf("This depends on implementation, but this is a double free that has returned 0 (success)\n");
  }
  printf("Success\n");
  exit(EXIT_SUCCESS);
}
