#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    void *ptr = Mem_Alloc(256);
    if (ptr != NULL) {
        Mem_Free(ptr, 0);
        printf("Simple allocation and free test passed\n");
    } else {
        printf("Simple allocation and free test failed\n");
    }
    return 0;
}