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
  printf("we will align a list of different byte chunks later and print the request and list\n");
  Mem_Dump();
  void* alloc_list[10];
  for(int i = 0; i < 10; i++) {
    alloc_list[i] = Mem_Alloc(3*i+1);
  }
  Mem_Dump();

  return 0;
}