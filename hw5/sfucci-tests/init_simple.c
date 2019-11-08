#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

/*
  Simple initialization. The dump should have the total memory be a multiple of a page size.*/


int main(){
  
  Mem_Init(1);
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
