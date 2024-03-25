#include "mem.h"
#include <stdio.h>
#include <string.h>

int main() {
    Mem_Init(4096);
    char *ptr = (char *)Mem_Alloc(256);
    if (ptr != NULL) {
        strcpy(ptr, "Hello, world!");
        if (strcmp(ptr, "Hello, world!") == 0)
            printf("Memory can be written to after allocation test passed\n");
        else
            printf("Memory can be written to after allocation test failed\n");
        Mem_Free(ptr, 0);
    } else {
        printf("Memory can be written to after allocation test failed\n");
    }
    return 0;
}