// Test 12: initialize and round up to 1 page
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mem.h"

#define FAIL -1

int main() {
    // only init for size 1 but should init with size of 1 page
    if (Mem_Init(1) == FAIL) {
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    return 0;
}
