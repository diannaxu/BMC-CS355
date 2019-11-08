#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

/*
Simple misuse checking
*/

int main(){
  if(Mem_Init(-1) == 0){
    printf("Failure\n");
    exit(EXIT_FAILURE);
  }

  printf("Success\n");
  exit(EXIT_SUCCESS);
}
