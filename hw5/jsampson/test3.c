#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr1 = Mem_Alloc(16);
    void *ptr2 = Mem_Alloc(32);
    void *ptr3 = Mem_Alloc(64);
    if (ptr1 != NULL && ptr2 != NULL && ptr3 != NULL)
        printf("Aligned allocations test passed\n");
    else
        printf("Aligned allocations test failed\n");
    Mem_Free(ptr1, 0);
    Mem_Free(ptr2, 0);
    Mem_Free(ptr3, 0);
    return 0;
}