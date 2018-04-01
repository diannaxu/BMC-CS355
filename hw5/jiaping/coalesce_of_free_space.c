#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define NUM_ALLOC 10
#define FREE_FREQ 100     // 1:100
#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

void test_8_byte() {
  int result = Mem_Init(8504);
  assert(result == 0);

  printf("--------------8 byte allocation-----------------\n");
  void* ptr0 = Mem_Alloc(8);
  if (ptr0 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr0 is at address %p.\n", ptr0);

  printf("--------------16 byte allocation-----------------\n");
  void* ptr1 = Mem_Alloc(16);
  if (ptr1 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr1 is at address %p.\n", ptr1);

  printf("--------------32 byte allocation-----------------\n");
  void* ptr2 = Mem_Alloc(32);
  if (ptr2 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr2 is at address %p.\n", ptr2);

  printf("--------------64 byte allocation-----------------\n");
  void* ptr3 = Mem_Alloc(64);
  if (ptr3 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr3 is at address %p.\n", ptr3);

  printf("--------------128 byte allocation-----------------\n");
  void* ptr4 = Mem_Alloc(128);
  if (ptr4 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr4 is at address %p.\n", ptr4);

  printf("--------------256 byte allocation-----------------\n");
  void* ptr5 = Mem_Alloc(256);
  if (ptr5 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr5 is at address %p.\n", ptr5);

  printf("--------------512 byte allocation-----------------\n");
  void* ptr6 = Mem_Alloc(512);
  if (ptr6 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr6 is at address %p.\n", ptr6);

  printf("--------------1024 byte allocation-----------------\n");
  void* ptr7 = Mem_Alloc(1024);
  if (ptr7 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr7 is at address %p.\n", ptr7);

  printf("--------------2048 byte allocation-----------------\n");
  void* ptr8 = Mem_Alloc(2048);
  if (ptr8 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr8 is at address %p.\n", ptr8);

  printf("--------------4096 byte allocation-----------------\n");
  void* ptr9 = Mem_Alloc(4096);
  if (ptr9 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr9 is at address %p.\n", ptr9);

  printf("--------------8 byte free-----------------\n");
  Mem_Free(ptr0, 1);
  Mem_Dump();

  printf("--------------16 byte free-----------------\n");
  Mem_Free(ptr1, 1);
  Mem_Dump();

  printf("--------------64 byte free-----------------\n");
  Mem_Free(ptr3, 1);
  Mem_Dump();

  printf("--------------256 byte free-----------------\n");
  Mem_Free(ptr5, 1);
  Mem_Dump();

  printf("--------------1024 byte free-----------------\n");
  Mem_Free(ptr7, 1);
  Mem_Dump();

  printf("--------------4096 byte free-----------------\n");
  Mem_Free(ptr9, 1);
  Mem_Dump();

  printf("--------------512 byte free-----------------\n");
  Mem_Free(ptr6, 1);
  Mem_Dump();


  end = clock();
  print_execution_time(begin, end);
  
}


int main() {
  test_8_byte();
  return EXIT_SUCCESS;
}