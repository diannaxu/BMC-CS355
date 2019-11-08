//init_test.c
//Tests initializing the memory allocator with valid and invalid arguments: first with a request of -1, then 0, then 10 (valid), then 100 (valid, but
//since the library is already initialized, it should fail). 
//Expected behavior: The assertions on the return value of Mem_Init execute successfully. m_error is E_BAD_ARGS (4) each time the initialization 
//fails and it is printed. 

#include <stdlib.h> 
#include <stdio.h> 
#include <assert.h> 
#include "mem.h"

#define ERROR -1 
#define SUCCESS 0 

int main(){

  assert(Mem_Init(-1) == ERROR);
  printf("m_error: %d\n", m_error);
  assert(Mem_Init(0) == ERROR);
  printf("m_error: %d\n", m_error);
  assert(Mem_Init(10) == SUCCESS);
  assert(Mem_Init(100) == ERROR);
  printf("m_error: %d\n", m_error);

  exit(EXIT_SUCCESS); 

}
