#include "mem.h"
#include <stdio.h>

int main() {
    if (Mem_Init(3000) == 0)
        printf("Initialize and round up to 1 page test passed\n");
    else
        printf("Initialize and round up to 1 page test failed\n");
    return 0;
}