#include "mem.h"
#include <stdio.h>

int main() {
    if (Mem_Init(4096) == 0)
        printf("Initialize with size of 1 page test passed\n");
    else
        printf("Initialize with size of 1 page test failed\n");
    return 0;
}