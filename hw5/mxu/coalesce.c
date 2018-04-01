#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>



int main() {
  if(Mem_Init(8192) < 0)
    printf("Sad, I failed\n");
  else
    printf("init successfully\n");
  printf("we will allocate several blocks and coalesce them\n");
  //Mem_Dump();
  void* alloc_list[10];
  for(int i = 0; i < 10; i++) {
    alloc_list[i] = Mem_Alloc(100);
  }
  Mem_Dump();
  Mem_Free(alloc_list[0],1);
  Mem_Free(alloc_list[3],1);
  Mem_Free(alloc_list[4],1);
  Mem_Free(alloc_list[5],1);
  Mem_Free(alloc_list[7],0);
  Mem_Free(alloc_list[9],1);
  Mem_Free(alloc_list[8],0);
  //Mem_Free(NULL,1);
  Mem_Dump();
  return 0;
}