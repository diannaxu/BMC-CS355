// Ziyao Wang
// 11/7/2021
// Test without coalesce

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define N 10

int main () {
    printf("Testing Mem_Init...\n");

    int result = Mem_Init(sizeof(int) * N);
    if (result != 0) {
        printf("Mem_Init failed.\n");
    } else {
        printf("Successfully requested memory region!\n");
    }

    printf("\n");

    printf("Testing Mem_Alloc...\n");

    int *ptr;
    ptr = Mem_Alloc(sizeof(int) * N);
    if (ptr == NULL || (long)ptr % 8 != 0){
        printf("Mem_Alloc failed.\n");
    } else {
        printf("Successfully allocated memory!\n");
        for(int i = 0; i < N; i++) {
            *(ptr+i) = i;
            printf("address: %p, value: %d\n", ptr+i, *(ptr+i));
        }
    }

    printf("\n");

    printf("Printing out all free chunks...\n");
    Mem_Dump();

    printf("\n");

    printf("Testing Mem_Free...\n");
    
    for (int i = 0; i < N; i++) {
        int result = Mem_Free(ptr+i, 0);
        if (result != 0) {
            printf("Failed to free chunk at %p\n", ptr+i);
        }
        Mem_Dump();
        printf("\n");
    }
}
