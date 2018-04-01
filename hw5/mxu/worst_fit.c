#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>



int main() {
  if(Mem_Init(2000) < 0)
    printf("Sad, I failed\n");
  else
    printf("init successfully\n");
  printf("we will align 10 blocks of 8 byte later, free several and then allocate one more to see whether we put into largest free block\n");
  Mem_Dump();
  void* alloc_list[10];
  for(int i = 0; i < 10; i++) {
    alloc_list[i] = Mem_Alloc(8);
  }
  Mem_Dump();
  Mem_Free(alloc_list[0],0);
  Mem_Free(alloc_list[1],0);
  void* test = Mem_Alloc(8);
  Mem_Dump();
  return 0;
}