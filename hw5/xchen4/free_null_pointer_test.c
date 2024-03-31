// Author: Paprika Chen
// Test for try to free a null pointer
// Right behavior: print: Successfully fail freeing a NULL pointer.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Attempt to free a NULL pointer
    void* nullPointer = NULL;
    if (Mem_Free(nullPointer, 0) == 0) { 
        return EXIT_FAILURE;
    }

    if (Mem_Free(nullPointer, 2) == 0) { 
        return EXIT_FAILURE;
    }

    printf("Successfully fail freeing a NULL pointer.\n");
    return EXIT_SUCCESS;
}
