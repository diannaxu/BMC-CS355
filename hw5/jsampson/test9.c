#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr = Mem_Alloc(128);
    if (ptr != NULL) {
        Mem_Free(ptr, 0);
        printf("Aligned allocation and free test passed\n");
    } else {
        printf("Aligned allocation and free test failed\n");
    }
    return 0;
}