#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr = Mem_Alloc(1);
    if ((unsigned long)ptr % 8 == 0)
        printf("8-byte alignment test passed\n");
    else
        printf("8-byte alignment test failed\n");
    Mem_Free(ptr, 0);
    return 0;
}