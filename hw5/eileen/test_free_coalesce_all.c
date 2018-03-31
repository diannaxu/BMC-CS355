#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

#define SUCCESS 0                                                                           
#define FAIL -1
#define TRUE 1
#define FALSE 0

int main(int argc, char** argv) {
  printf("* A simple test for Mem_Free with coalesce\n");
  printf("* Also checked for invalid free pointers\n");
  printf("* Check memory dump for results\n");

  printf("* Testing Invalid free: free NULL pointers\n");
  if(Mem_Free(NULL, FALSE) != FAIL) {
    printf("Freed null pointer\n");
    printf("Test failed\n");
    exit(EXIT_FAILURE);
  }
  long regionsize = 4100;
  if(Mem_Init(regionsize) == FAIL) {
    printf("Init failed\n");
    printf("Test failed\n");
    exit(EXIT_FAILURE);
  }

  long size_one = 1;
  long size_two = 20000;
  long size_three = 2000;
  void* region_one = Mem_Alloc(size_one);
  printf("* region_one starts at %p\n", region_one);
  void* region_two = Mem_Alloc(size_two);
  printf("* region_two starts at %p\n", region_two); 
  void* region_three = Mem_Alloc(size_three);
  printf("* region_three starts at %p\n", region_three); 
  if(region_one == NULL) {
    printf("Alloc region_one failed. Test failed\n");
    exit(EXIT_FAILURE);
  }
  if(region_two == NULL) {
    printf("Alloc region_two failed. Test failed\n");
    exit(EXIT_FAILURE);
  } 
  if(region_three == NULL) {
    printf("Alloc region_three failed. Test failed\n");
    exit(EXIT_FAILURE);
  }

  printf("* Free region_one\n");
  if(Mem_Free(region_one, FALSE) == FAIL) {
    printf("Free region_one failed\n");
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("* Free region_two\n");
  if(Mem_Free(region_two, FALSE) == FAIL) {
    printf("Free region_two failed\n");
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("* Free region_three coalesce all\n");
  if(Mem_Free(region_three, TRUE) == FAIL) {
    printf("Free region_three failed\n");
    exit(EXIT_FAILURE);
  }
  Mem_Dump();

  long size_four = 4999;
  void* region_four = Mem_Alloc(size_four);
  printf("* region_four starts at %p\n", region_four);  
  if(region_four == NULL) {
    printf("Alloc region_four failed %d. Test failed\n", m_error);                                                        
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("* Free region_four\n");
  if(Mem_Free(region_four, TRUE) == FAIL) {
    printf("Free region_four failed\n");
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  if(Mem_Free(region_four, TRUE) == TRUE) {
    printf("Double freed!\n");
    printf("Test failed\n");
    exit(EXIT_FAILURE);
  }
  printf("Test passed!\n");
}
