#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr1 = Mem_Alloc(1024);
    void *ptr2 = Mem_Alloc(512);
    void *ptr3 = Mem_Alloc(1024);
    if (ptr1 != NULL && ptr2 != NULL && ptr3 != NULL)
        printf("Worst-fit allocation test passed\n");
    else
        printf("Worst-fit allocation test failed\n");
    Mem_Free(ptr1, 0);
    Mem_Free(ptr2, 0);
    Mem_Free(ptr3, 0);
    return 0;
}