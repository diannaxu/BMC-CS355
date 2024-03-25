#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr = Mem_Alloc(8);
    if (ptr != NULL)
        printf("Simple 8-byte allocation test passed\n");
    else
        printf("Simple 8-byte allocation test failed\n");
    Mem_Free(ptr, 0);
    return 0;
}