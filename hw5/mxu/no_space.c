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
  printf("we will align 10 blocks of 200 byte later to run out of memory\n");
  Mem_Dump();
  void* alloc_list[10];
  for(int i = 0; i < 10; i++) {
    alloc_list[i] = Mem_Alloc(200);
  }
  Mem_Dump();
  printf("we should run out of memory now, next malloc will fail\n")
  void* test = Mem_Alloc(8);
  Mem_Dump();
  return 0;
}