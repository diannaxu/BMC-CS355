/*
Test for 8 byte allocation
request made for 8-divisble sizes
Use assert to make sure returned pointer address is divisible by 8.
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

int main() {
  int requested = Mem_Init(800);
  assert(requested == SUCCESS);

  printf("Request for 8 bytes.\n");
  void *ptr1 = Mem_Alloc(8);
  assert(ptr1 != NULL);
  printf("ptr1 address: %p\n", ptr1);
  assert((long long)ptr1%EIGHT_BYTES == SUCCESS);

  printf("Request for 16 bytes.\n");
  void *ptr2 = Mem_Alloc(16);
  assert(ptr2 != NULL);
  printf("ptr2 address: %p\n", ptr2);
  assert((long long)ptr2%EIGHT_BYTES == SUCCESS);

  printf("Request for 64 bytes.\n");
  void *ptr3 = Mem_Alloc(64);
  assert(ptr3 != NULL);
  printf("ptr3 address: %p\n", ptr3);
  assert((long long)ptr3%EIGHT_BYTES == SUCCESS);

  printf("Request for 128 bytes.\n");
  void *ptr4 = Mem_Alloc(128);
  assert(ptr4 != NULL);
  printf("ptr4 address: %p\n", ptr4);
  assert((long long)ptr4%EIGHT_BYTES == SUCCESS);

  printf("Request for 256 bytes.\n");
  void *ptr5 = Mem_Alloc(256);
  assert(ptr5 != NULL);
  printf("ptr5 address: %p\n", ptr5);
  assert((long long)ptr5%EIGHT_BYTES == SUCCESS);

  exit(EXIT_SUCCESS);
}
