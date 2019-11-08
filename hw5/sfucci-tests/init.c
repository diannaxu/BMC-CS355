#include "../mem.h"
#include <stdlib.h>

#define PAGE_SIZE 4096

/*
Simple initialization. The dump should not have exactly 4096, but a multiple of it. This is, of course, based off of the page size of 4096 on my machine
*/

int main(){
  if(Mem_Init(PAGE_SIZE) == -1){
    exit(EXIT_FAILURE);
  }

  Mem_Dump();
  
  exit(EXIT_SUCCESS);
}
