/*
Test for odd sized allocation
Use assert to make sure round up for odd-size alloc is as expected
Expected behavior: exit normally
*/

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1
#define EIGHT_BYTES 8
#define HEADER_SIZE 24

int main() {
  int requested = Mem_Init(800);
  assert(requested == SUCCESS);

  printf("Request for 1 bytes.\n");
  void *ptr1 = Mem_Alloc(1);
  assert(ptr1 != NULL);
  printf("ptr1 address: %p\n", ptr1);
  assert((long long)ptr1%EIGHT_BYTES == SUCCESS);

  printf("Request for 27 bytes.\n");
  void *ptr2 = Mem_Alloc(27);
  assert(ptr2 != NULL);
  printf("ptr2 address: %p\n", ptr2);
  assert((long long)ptr2%EIGHT_BYTES == SUCCESS);

  assert((long long)ptr2-(long long)ptr1-HEADER_SIZE == 8);
  printf("Success: Returned space for 1 byte request is 8.\n");

  printf("Request for 45 bytes.\n");
  void *ptr3 = Mem_Alloc(45);
  assert(ptr3 != NULL);
  printf("ptr3 address: %p\n", ptr3);
  assert((long long)ptr3%EIGHT_BYTES == SUCCESS);

  assert((long long)ptr3-(long long)ptr2-HEADER_SIZE == 32);
  printf("Success: Returned space for 27 byte request is 32.\n");

  printf("Request for 123 bytes.\n");
  void *ptr4 = Mem_Alloc(123);
  assert(ptr4 != NULL);
  printf("ptr4 address: %p\n", ptr4);
  assert((long long)ptr4%EIGHT_BYTES == SUCCESS);

  assert((long long)ptr4-(long long)ptr3-HEADER_SIZE == 48);
  printf("Success: Returned space for 45 byte request is 48.\n");

  printf("Request for 511 bytes.\n");
  void *ptr5 = Mem_Alloc(511);
  assert(ptr5 != NULL);
  printf("ptr5 address: %p\n", ptr5);
  assert((long long)ptr5%EIGHT_BYTES == SUCCESS);

  assert((long long)ptr5-(long long)ptr4-HEADER_SIZE == 128);
  printf("Success: Returned space for 123 byte request is 128.\n");
  exit(EXIT_SUCCESS);
}
