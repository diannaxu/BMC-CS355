// free_invalid_ptr.c
// Accessing memory beyond the allocated region didn't cause a segmentation fault

#include <stdio.h>
#include "mem.h"

int main() {
    if (Mem_Init(4096) != 0) {
        printf("Initialization failed.\n");
        return 1;
    }

    void *ptr = Mem_Alloc(4000);
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Attempt to access memory beyond the allocated region
    printf("Attempting to access memory beyond the allocated region...\n");
    void *invalid_ptr = (void *)((char *)ptr + 20000); // Pointing beyond the allocated memory
    Mem_Free(invalid_ptr, 0);

    printf("m_error is %d\n", m_error);

    printf("Accessing memory beyond the allocated region didn't cause a segmentation fault.\n");

    return 0;
}
