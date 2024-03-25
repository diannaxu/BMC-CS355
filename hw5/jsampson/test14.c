#include "mem.h"
#include <stdio.h>

int main() {
    Mem_Init(4096);
    if (Mem_Free(NULL, 0) == 0)
        printf("Try to free a NULL pointer test passed\n");
    else
        printf("Try to free a NULL pointer test failed\n");
    return 0;
}