/*
 * test #13
 * File: no-space.c
 * Purpose: testing what happens when we run out of space
 * Expected Result: E_NO_SPACE (1) is the value of m_error because we run out of space
 */
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAILURE -1
#define BLOCK 500


int main() {
  if(Mem_Init(BLOCK)==FAILURE) return EXIT_FAILURE;
  Mem_Dump();
  void* ptr1 = Mem_Alloc(300);
  void* ptr2 = Mem_Alloc(300);

  printf("This is the value of m_error: %d, if is 1, then the test passes because E_NO_SPACE is its value \n",  m_error);



}
