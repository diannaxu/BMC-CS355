// Test 2: simple 8-byte allocation
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

    void *ptr = Mem_Alloc(8);

    printf("Pointer address: %p\n", ptr);

    return 0;
}
