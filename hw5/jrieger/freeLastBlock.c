#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

#define DATA_SIZE 20

int main() {
    // Initialize memory region
    if (Mem_Init(4096) != 0) {
        fprintf(stderr, "Error: Failed to initialize memory\n");
        return EXIT_FAILURE;
    }

    // Allocate memory
    void *ptr1 = Mem_Alloc(DATA_SIZE);
    if (ptr1 == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    // Write some data to the allocated memory
    char data1[DATA_SIZE] = "This is data 1";
    memcpy(ptr1, data1, strlen(data1) + 1);

    // Free the allocated memory block
    if (Mem_Free(ptr1, NO_COALESCE) != 0) {
        fprintf(stderr, "Error: Failed to free memory\n");
        return EXIT_FAILURE;
    }

    printf("First memory block freed successfully\n");

    // Allocate memory again
    void *ptr2 = Mem_Alloc(DATA_SIZE);
    if (ptr2 == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    // Write some data to the allocated memory
    char data2[DATA_SIZE] = "This is data 2";
    memcpy(ptr2, data2, strlen(data2) + 1);

    // Free the last allocated memory block
    if (Mem_Free(ptr2, NO_COALESCE) != 0) {
        fprintf(stderr, "Error: Failed to free memory\n");
        return EXIT_FAILURE;
    }

    printf("Second memory block freed successfully\n");

    // Try to allocate memory again
    void *ptr3 = Mem_Alloc(DATA_SIZE);
    if (ptr3 == NULL) {
        printf("Last memory block freed successfully\n");
    } else {
        fprintf(stderr, "Error: Memory allocation should have failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
