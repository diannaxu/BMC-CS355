/*
    Author: Esther(Xinning) Fang
    Check coalesce with 0, 1 and 2 and freeing a NULL pointer
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(4096) == -1) {
        printf("Error when initilizing.\n");
        exit(EXIT_FAILURE);
    }

    void *ptrs[3];
    for (int i = 0; i < 3; i++) {
        ptrs[i] = Mem_Alloc(8);
        if (ptrs[i] == NULL) {
            printf("Error during allocation.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("After allocating three 8-byte blocks:\n");
    Mem_Dump();

    for (int i = 0; i < 3; i++) {
      if (Mem_Free(ptrs[i], 0) == -1) {
        printf("Error when freeing ptrs[%d]\n", i);
        exit(EXIT_FAILURE);
      }
    }
    printf("After free the three 8-byte blocks:\n");
    Mem_Dump(); // Should have 4 free chunks, with the first 3 chunks having (32+8) bytes

    printf("Allocating a fourth 8-byte block:\n");
    void *ptr4 = Mem_Alloc(8);
    if (ptr4 == NULL) {
        printf("Error during allocation.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    printf("Free the fourth block with coalesce = 2:\n");
    if (Mem_Free(ptr4, 2) == -1){
      printf("Error when freeing ptr4\n");
      exit(EXIT_FAILURE);
    }
    // With 3 free chunks left as the chunk where ptr3 located and the last chunk were coalesced
    Mem_Dump();

    printf("Allocating another 8-byte block:\n");
    void *ptr5 = Mem_Alloc(8);
    if (ptr5 == NULL) {
        printf("Error during allocation.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    printf("Mem_Free(NULL, 1):\n");
    if (Mem_Free(NULL, 1) == -1) {
      printf("Error when freeing NULL\n");
      exit(EXIT_FAILURE);
    }
    Mem_Dump(); // The first two free chunks should be coalesced, with ptr5 not free and the rest free

    return EXIT_SUCCESS;
}
