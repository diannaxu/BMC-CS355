// Test 5: check error handling for bad arguments to Mem_Init
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    // negative size
    if (Mem_Init(1024) == FAIL){
        if (m_error == E_BAD_ARGS) {
            printf("init failed with bad arguments -- expected\n");
        }
    }
    
    if (Mem_Init(16) == FAIL){
        printf("Can't init -- NOT EXPECTED\n");
        exit(EXIT_FAILURE);
    }

    printf("Initialized. Now trying to init again.\n");

    if (Mem_Init(16) == FAIL){
        printf("failed due to init twice -- expected\n");
    }

    return 0;
}
