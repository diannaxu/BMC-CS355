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
  printf("we will align 8 byte chunk later and print the list\n");
  Mem_Dump();
  void* test = Mem_Alloc(8);
  Mem_Dump();

  return 0;
}