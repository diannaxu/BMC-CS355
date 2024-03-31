// Author: Paprika Chen
// Test for Aligned and Odd-Sized Allocations.
// Right behavior: print: Nothing is printed.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    long sizeOfRegion = 1024; // Example size, adjust as needed
    int initResult = Mem_Init(sizeOfRegion);

    if (initResult == 0) {
        printf("Mem_Init succeeded.\n");
    } else {
        printf("Mem_Init failed.\n");
        return -1; // Exit if initialization failed
    }


    return 0;
}