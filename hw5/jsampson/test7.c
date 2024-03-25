#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr1 = Mem_Alloc(1024);
    void *ptr2 = Mem_Alloc(512);
    Mem_Free(ptr1, 0);
    Mem_Free(ptr2, 1);
    void *ptr3 = Mem_Alloc(1536);
    if (ptr3 != NULL)
        printf("Coalesce of free space test passed\n");
    else
        printf("Coalesce of free space test failed\n");
    Mem_Free(ptr3, 0);
    return 0;
}