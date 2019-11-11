/*
 * test #15
 * File: writeable.c
 * Purpose: Checks if memory is writeable
 * Expected Output: After string is written to memory allocated, if it prints that string, the test is successful.
 */
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BLOCK 5000
#define FAILURE -1

int main() {
  if(Mem_Init(BLOCK) == FAILURE) exit(EXIT_FAILURE);
  //Mem_Dump();
  char *ptr = (char*) Mem_Alloc(25*sizeof(char));
  //Mem_Dump();
  char *str = "Memory is writable\n";
  printf("String is %s", str);
  printf("copying over string to ptr\n");
  strncpy(ptr,str, 25*sizeof(char));
  printf("If string prints, memory is actually writeable.\n");
  printf("ptr is now the following string: %s", ptr);
  //Mem_Dump();

}
