// Test 15: check that memory can be written to after allocation
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(1024) == FAIL) {
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }
    
    void *ptr = Mem_Alloc(64);

    if (ptr != NULL) {
        // write to memory
        *((int *)ptr) = 4; 
        printf("Value at pointer address: %d\n", *((int *)ptr));
        printf("The program should output value of 4. \n");
    }

    if(Mem_Free(ptr, 1) == FAIL){
        printf("Can't free ptr\n");
        exit(EXIT_FAILURE);
    }
    
    Mem_Dump();
    
    return 0;
}
