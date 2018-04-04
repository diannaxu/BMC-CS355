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
#include "ll.h"

#define PAGE 4096
#define HEADER 32
#define WORST_CASE 40

#define FAILURE -1

// 1. check for 8-byte alignment
int eight_byte() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
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
    free(ptrs);
    return TRUE;
  }
}

// 2. allocate exactly 8 bytes
int simple_eight_byte() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
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
    free(ptrs);
    return TRUE;
  }
}
// 3. make multiple allocations of size that's a multiple of 8
int aligned_allocations() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    void **ptrs = malloc(sizeof(void *) *30);
    int j = 8;
    for (int i = 0; i < 100; i+=8) {
      ptrs[i] = Mem_Alloc(i);
      if (ptrs[i] == NULL) {
        return FALSE;
      }
      if (((long) ptrs[i] % 8 != 0)) {
        return FALSE;
      }
      j+=j;
    }
    free(ptrs);
    return TRUE;
  }
}

// 4. make multiple allocations of odd number size
int odd_allocations() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
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
    free(ptrs);
    return TRUE;
  }
}

// 5. Pass invalid arguments to Mem_Init()
int invalid_mem_init() {
  int ret = Mem_Init(-1);
  if (ret == EXIT_FAILURE) {
    // we get an error, what we expect with a -1 passed in
    return TRUE;
  } else {
    return FALSE;
  }
}

// 6. Worstfit allocation
int worst_fit() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    void **ptrs = malloc(sizeof(void *) * 5);
    int large_size = 2400;
    for (int i = 0; i < 5; i++) {
      ptrs[i] = Mem_Alloc(i);
      if (ptrs[i] == NULL || (long) ptrs[i] % 8 != 0) {
        return FALSE;
      }
      if (i == 2) {
        ptrs[i] = Mem_Alloc(large_size);
      }
      if (i == 3) {
        ptrs[i] = Mem_Alloc(i);
      }
    }
    if (ptrs[3] - ptrs[2] != large_size + HEADER + WORST_CASE) {
      return FALSE;
    }
  }
  return TRUE;
}

// 7. Coalesce of free space
int coalesce_test() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    void **ptrs = malloc(sizeof(void *) * 5);
    for (int i = 0; i < 500; i+=99) {
      ptrs[i] = Mem_Alloc(i);
      if (ptrs[i] == NULL || (long) ptrs[i] % 8 != 0) {
        return FALSE;
      }
    }
    printf("\tBefore freeing the lists look like: \n");
    // Mem_Dump();

    Mem_Free(ptrs[2], FALSE);
    Mem_Free(ptrs[3], TRUE);
    printf("\tAfter freeing 2, and 3 of the list: \n");
    // Mem_Dump();
    Mem_Free(ptrs[4], TRUE);

    printf("\tAfter freeing 4 of the list: \n");
    // Mem_Dump();
  }
  return TRUE;
}

// 8. Simple allocation and free
int simple_alloc_free() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    void *ret;
    ret = Mem_Alloc(100);
    printf("\tWe just called Mem_Alloc(100)\n");
    // Mem_Dump();
    Mem_Free(ret, FALSE);
    printf("\tFreed that pointer, it is on the free list\n");
    // Mem_Dump();
  }
  return TRUE;
}

// 9. Aligned allocation and free
int aligned_alloc_free(){
  // Basically same as 8 but called with a multiple of 8 in Mem_Alloc
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    void *ret;
    ret = Mem_Alloc(160);
    printf("\tWe just called Mem_Alloc(160)\n");
    // Mem_Dump();
    Mem_Free(ret, FALSE);
    printf("\tFreed that pointer, it is on the free list\n");
    // Mem_Dump();
  }
  return TRUE;
}

// 10. Odd-sized allocation and free
// This is like 8 and 9 but called with an odd number!
int odd_alloc_free() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    void *ret;
    ret = Mem_Alloc(77);
    printf("\tWe just called Mem_Alloc(77)\n");
    // Mem_Dump();
    Mem_Free(ret, FALSE);
    printf("\tFreed that pointer, it is on the free list\n");
    // Mem_Dump();
  }
  return TRUE;
}

// 11. Initialize with size of 1 page
int initialize_page_size() {
  // I've been testing this in every other test
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    return TRUE;
  }
}

// 12. Initialize and round up to one page
int initialize_size_one() {
  if (Mem_Init(1) != 0) {
    return EXIT_FAILURE;
  } else {
    return TRUE;
  }
}

// 13. no space left to allocate
int no_space_left() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    if (Mem_Alloc(PAGE*PAGE) == NULL) { // the behavior we expect
      return TRUE;
    }
    return FALSE;
  }
}

// 14. Free a NULL pointer
int free_null_ptr() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    if (Mem_Free(NULL, 0) == EXIT_FAILURE) {
      return FALSE;
    }
    if (Mem_Free(NULL, 1) == EXIT_FAILURE) {
      return FALSE;
    }
    return TRUE;
  }
}

// 15. Check that memory can be written to after allocation
int test_malloc() {
  if (Mem_Init(PAGE) != 0) {
    return EXIT_FAILURE;
  } else {
    char *string = Mem_Alloc(15);
    string[0] = 'n';
    string[1] = 'e';
    string[2] = 'e';
    string[3] = 'd';
    string[4] = ' ';
    string[5] = 's';
    string[6] = 'l';
    string[7] = 'e';
    string[8] = 'e';
    string[9] = 'p';
    string[10] = '\0';
    printf("%s\n", string);
    return TRUE;
  }
}

int main() {

  printf("-----Beginning test cases!-----\n");
  printf("\nTest 1: 8 byte alignment\n");
  printf("RESULT: %s\n", eight_byte() == TRUE ? "PASSED" : "FAILED");
  printf("-------------------------\n");
  printf("\nTest 2: Simple 8 byte allocation\n");
  printf("RESULT: %s\n", simple_eight_byte() == TRUE ? "PASSED" : "FAILED");
  printf("-------------------------\n");
  printf("\nTest 3: Multiple aligned allocations\n");
  printf("RESULT: %s\n", aligned_allocations() == TRUE ? "PASSED" : "FAILED");
  printf("-------------------------\n");
  printf("\nTest 4: Multiple odd number size allocations\n");
  printf("RESULT: %s\n", odd_allocations() == TRUE ? "PASSED" : "FAILED");
  printf("-------------------------\n");
  printf("\nTest 5: Invalid Mem_Init()\n");
  printf("RESULT: %s\n", invalid_mem_init() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 6: Worst fit allocation\n");
  printf("RESULT: %s\n", worst_fit() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 7: Coalescing\n");
  printf("RESULT: %s\n", coalesce_test() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 8: Simple Allocation and Free\n");
  printf("RESULT: %s\n", simple_alloc_free() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 9: Simple Aligned Allocation and Free\n");
  printf("RESULT: %s\n", aligned_alloc_free() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 10: Simple Odd Number Allocation and Free\n");
  printf("RESULT: %s\n", odd_alloc_free() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 11: Initialize with size of 1 page\n");
  printf("RESULT: %s\n", initialize_page_size() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 12: Initialize and round up to size of 1 page\n");
  printf("RESULT: %s\n", initialize_size_one() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 13: No space to allocate\n");
  printf("RESULT: %s\n", no_space_left() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 14: Free a NULL pointer\n");
  printf("RESULT: %s\n", free_null_ptr() == TRUE ? "PASSED" : "FAILED");
  printf("\nTest 15: Writing to the memory we allocated\n");
  printf("RESULT: %s\n", test_malloc() == TRUE ? "PASSED" : "FAILED");
  printf("-----End of test cases! Yay!-----\n");
}
