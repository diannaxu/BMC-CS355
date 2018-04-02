#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "mem.h"
#define TRUE 1
#define FALSE 0
#define PAGE 4096

// helper function to free the arrays of pointers we make using malloc
void free_ptrs(void **ptrs) {
  for (int i = 0; ptrs[i] != NULL; i++) {
    free(ptrs[i]);
  }
}

// 1. check for 8-byte alignment
int eight_byte() {
  void **ptrs = malloc(sizeof(void *) *30);
  for (int i = 0; i < 30; i++) {
    ptrs[i] = Mem_Alloc(7);
    if (ptrs[i] == NULL) {
      return FALSE;
    }
    if (((long) ptrs[i] % 8 != 0)) {
      return FALSE;
    }
  }
  free_ptrs(ptrs);
  return TRUE;
}

// 2. allocate exactly 8 bytes
int simple_eight_byte() {
  void **ptrs = malloc(sizeof(void *) *30);
  for (int i = 0; i < 30; i++) {
    ptrs[i] = Mem_Alloc(8);
    if (ptrs[i] == NULL) {
      return FALSE;
    }
    if (((long) ptrs[i] % 8 != 0)) {
      return FALSE;
    }
  }
  free_ptrs(ptrs);
  return TRUE;
}

// 3. make multiple allocations of size that's a multiple of 8
int aligned_allocations() {
  void **ptrs = malloc(sizeof(void *) *30);
  int j = 8;
  for (int i = 0; i < 30; i++) {
    ptrs[i] = Mem_Alloc(j);
    if (ptrs[i] == NULL) {
      return FALSE;
    }
    if (((long) ptrs[i] % 8 != 0)) {
      return FALSE;
    }
    j+=j;
  }
  free_ptrs(ptrs);
  return TRUE;
}

// 4. make multiple allocations of odd number size
int odd_allocations() {
  void **ptrs = malloc(sizeof(void *) *30);
  int j = 1;
  for (int i = 0; i < 30; i++) {
    ptrs[i] = Mem_Alloc(j);
    if (ptrs[i] == NULL) {
      return FALSE;
    }
    if (((long) ptrs[i] % 8 != 0)) {
      return FALSE;
    }
    j+=2;
  }
  free_ptrs(ptrs);
  return TRUE;
}

// 5. Pass invalid arguments to Mem_Init()
int invalid_mem_init() {
  int ret = Mem_Init(-1);
  if (ret == -1) {
    // we get an error, what we expect with a -1 passed in
    free_ptrs(ptrs);
    return TRUE;
  } else {
    return FALSE;
  }
}


int main() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    printf("Test 1: 8 byte alignment\n");
    printf("RESULT: %s\n", eight_byte() == TRUE ? "PASSED" : "FAILED");
    printf("-------------------------\n");
    printf("Test 2: Simple 8 byte allocation\n");
    printf("RESULT: %s\n", simple_eight_byte() == TRUE ? "PASSED" : "FAILED");
    printf("-------------------------\n");
    printf("Test 3: Multiple aligned allocations\n");
    printf("RESULT: %s\n", aligned_allocations() == TRUE ? "PASSED" : "FAILED");
    printf("-------------------------\n");
    printf("Test 4: Multiple odd number size allocations\n");
    printf("RESULT: %s\n", odd_allocations() == TRUE ? "PASSED" : "FAILED");
    printf("-------------------------\n");
    printf("Test 5: Invalid Mem_Init()\n");
    printf("RESULT: %s\n", invalid_mem_init() == TRUE ? "PASSED" : "FAILED");
  }
}
