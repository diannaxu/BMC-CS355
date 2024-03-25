// Test 11: initialize with size of 1 page
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(getpagesize()) == FAIL) {
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    return 0;
}
