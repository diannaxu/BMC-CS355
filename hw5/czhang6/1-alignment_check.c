// Test 1: check for 8-byte alignment
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(1024) == FAIL){
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }
    
    void *ptr = Mem_Alloc(1);

    printf("Pointer address: %p\n", ptr);
    printf("The pointer address should end with 0 or 8.\n");

    return 0;
}
