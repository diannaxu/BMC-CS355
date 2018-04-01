#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>



int main() {
  if(Mem_Init(4096) < 0)
    printf("Sad, I failed\n");
  else
    printf("init successfully\n");
  printf("The remaining space for user to malloc should be 4096\n");
  return 0;
}