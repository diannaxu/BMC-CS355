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
#define FAILURE -1
#define PAGE 4096

// helper function to free the pointers from calling malloc
void free_ptrs(void **ptrs) {
  for (int i = 0; ptrs[i] != NULL; i++) {
    printf("freeing all pointers\n");
    if(Mem_Free(ptrs[i], FALSE) == FAILURE) {
      printf("mem_free is not working\n");
    }
  }
}


//testing eight_byte_alignment
//can also be used to check several odd-sized allocations by changing parameter passed in
//can also be used for simple allocation and free
int eight_byte_alignment(int alloc) {
  if (Mem_Init(PAGE) == FAILURE ) {
      printf("Mem_Init FAILURE\n");
      return FALSE;
  } else {
    int size = 10;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size; i++) {
      ptrs[i] = Mem_Alloc(alloc);
      if (ptrs[i] == NULL) {
        return FALSE;
      }
      if (((long) ptrs[i] % 8 != 0)) {
        return FALSE;
      }
    }

    printf("\tPRINTING LIST\n");
    printf("\tshould see 8 byte allocations\n");
    Mem_Dump();

    free_ptrs(ptrs);

    return TRUE;
  }
}


//testing simple 8-byte allocation
int simple_eight_byte() {
  if (Mem_Init(PAGE) == FAILURE ) {
    printf("Mem_Init FAILURE\n");
    return FALSE;
  } else {
    int size = 10;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size; i++) {
      ptrs[i] = Mem_Alloc(8);
      if (ptrs[i] == NULL) {
        return FALSE;
      }
      if (((long) ptrs[i] % 8 != 0)) {
        return FALSE;
      }
    }

    printf("\tPRINTING LIST\n");
    printf("\tshould see 8 byte allocations\n");
    Mem_Dump();

    free_ptrs(ptrs);

    return TRUE;
  }
}


//testing few_aligned_allocations
//can also be used for aligned allocation and free
int few_aligned_allocations() {
  if (Mem_Init(PAGE) == FAILURE ) {
      printf("Mem_Init FAILURE\n");
      return FALSE;
  } else {
    int size = 10;
    int alloc = 8;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size; i++) {
      ptrs[i] = Mem_Alloc(alloc);
      if (ptrs[i] == NULL) {
        return FALSE;
      }
      if (((long) ptrs[i] % 8 != 0)) {
        return FALSE;
      }
    }
    alloc+=8;

    printf("\tPRINTING LIST\n");
    printf("\tshould see 8 byte allocations\n");
    Mem_Dump();

    free_ptrs(ptrs);

    return TRUE;
  }
}


//testing few_aligned_allocations
int bad_args_to_mem_init() {
  if (Mem_Init(PAGE) == FAILURE) {
    printf("Mem_Init FAILURE with PAGE\n");
    return FALSE;
  } else if(Mem_Init(-1) == FAILURE) {
    printf("Mem_Init FAILURE with -1\n");
    return FALSE;
  } else {
    printf("Mem_Init worked!\n");
    return TRUE;
  }
}

//testing worsefit allocation
int worsefit_allocation() {
  if (Mem_Init(PAGE) == FAILURE) {
    printf("Mem_Init FAILURE with PAGE\n");
    return FALSE;
  } else {
    int size = 10;
    int alloc = 12;
    int worst = 20;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size; i++) {
      ptrs[i] = Mem_Alloc(alloc);
    }

    //free a random pointer
    if(Mem_Free(ptrs[4], FALSE) == FAILURE) {
      printf("Mem_Free did NOT work\n");
      return FALSE;
    }

    //allocate something else to check if this was placed in worse fit
    Mem_Alloc(worst);

    printf("\tPRINTING LIST\n");
    printf("\tshould see that allocating 20 bytes was placed in the worst fit\n");
    Mem_Dump();

    free_ptrs(ptrs);

    return TRUE;

  }
}


//testing coalesce of free space
int coalesce() {
  if (Mem_Init(PAGE) == FAILURE) {
    printf("Mem_Init fail with PAGE\n");
    return FALSE;
  } else {
    int size = 10;
    int alloc = 12;
    int worst = 20;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size; i++) {
      ptrs[i] = Mem_Alloc(alloc);
    }
    printf("\tPRINTING LIST BEFORE FREEING\n");
    Mem_Dump();

    Mem_Free(ptrs[2],TRUE);
    printf("\tfreeing pointer at index 2 -- CHECK TO SEE IF COALESCE \n");
    Mem_Dump();

    Mem_Free(ptrs[4],TRUE);
    printf("\tfreeing pointer at index 4 -- CHECK TO SEE IF COALESCE \n");
    Mem_Dump();

    Mem_Free(ptrs[8],TRUE);
    printf("\tfreeing pointer at index 9 -- CHECK TO SEE IF COALESCE \n");
    Mem_Dump();

    free_ptrs(ptrs);
    return TRUE;

  }
}

//testing initialize_with_page_size
//tests for any page size passed in
int initialize_with_page_size(int p_size) {
  if (Mem_Init(p_size) == FAILURE) {
    printf("Mem_Init FAILURE with p_size of %d :(((( \n", p_size);
    return FALSE;
  } else {
    printf("Mem_Init worked with p_size of %d :))) \n", p_size);
    return TRUE;
  }
}

//testing no_space_left_to_allocate
int no_space_left_to_allocate() {
  if (Mem_Init(PAGE) == FAILURE ) {
    printf("Mem_Init FAILURE\n");
    return FALSE;
  } else {
    int size = 17;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size -1 ; i++) {
      ptrs[i] = Mem_Alloc(256);
      if (ptrs[i] == NULL) {
        return FALSE;
      }
    }

    printf("\tPRINTING LIST after initial allocation \n");
    Mem_Dump();

    printf("allocating one more which should NOT work\n");
    ptrs[size-1] = Mem_Alloc(10);

    printf("\tPRINTING LIST again\n");
    Mem_Dump();

    free_ptrs(ptrs);

    return TRUE;
  }
}


//testing free_null_pointer
int free_null_pointer() {
  if (Mem_Init(PAGE) == FAILURE ) {
    printf("Mem_Init FAILURE\n");
    return FALSE;
  } else {
    void *p = NULL;
    if(Mem_Free(p, FALSE) == FAILURE) {
      return TRUE;
    } else {
      return FALSE;
    }
  }
}



//testing memory_written_after_allocation
int memory_written_after_allocation() {
  if (Mem_Init(PAGE) == FAILURE ) {
    printf("Mem_Init FAILURE\n");
    return FALSE;
  } else {
    int size = 10;
    int alloc = 10;
    void **ptrs = malloc(sizeof(void*) * size);
    for (int i = 0; i < size; i++) {
      ptrs[i] = Mem_Alloc(alloc);
      if (ptrs[i] == NULL) {
        return FALSE;
      }
    }
    printf("\tPRINTING LIST after initial allocation \n");
    Mem_Dump();

    free_ptrs(ptrs);

    printf("\tPRINTING LIST -- check to see if list is free\n");
    Mem_Dump();

    void *p = Mem_Alloc(200);

    printf("\tPRINTING LIST -- check to see if allocating 200 bytes works properly\n");
    Mem_Dump();

    Mem_Free(p, FALSE);

    return TRUE;
  }
}


int main() {
    printf("------------\n");
    printf("eight_byte_alignment/several odd-sized allocations/simple_allocation_and_free -- testing with 3: %s\n", eight_byte_alignment(3) == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("eight_byte_alignment/several odd-sized allocations/simple_allocation_and_free -- testing with 9: %s\n", eight_byte_alignment(9) == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("simple_eight_byte: %s\n", simple_eight_byte() == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("few_aligned_allocations/aligned_allocation_and_free: %s\n", few_aligned_allocations() == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("bad_args_to_mem_init: %s\n", bad_args_to_mem_init() == TRUE ? "it worked!" : "oh no :(");
    printf("------------\n");
    printf("worsefit_allocation: %s\n", worsefit_allocation() == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("coalesce: %s\n", coalesce() == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("initialize_with_page_size -- size PAGE: %s\n", initialize_with_page_size(PAGE) == TRUE ? "it worked!" : "oh no :(");
    printf("------------\n");
    printf("initialize_with_page_size -- size 1948: %s\n", initialize_with_page_size(1948) == TRUE ? "it worked!" : "oh no :(");
    printf("------------\n");
    printf("no_space_left_to_allocate: %s\n", no_space_left_to_allocate() == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("------------\n");
    printf("free_null_pointer: %s\n", free_null_pointer() == TRUE ? "it worked!" : "oh no :(");
    printf("------------\n");
    printf("memory_written_after_allocation: %s\n", memory_written_after_allocation() == TRUE ? "basic measures passed, make sure to also check mem_dump" : "oh no :(");
    printf("\n\n\nall tests done\n");
}
