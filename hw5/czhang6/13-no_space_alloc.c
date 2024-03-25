// Test 13: no space left to allocate
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
    
    // this alloc that should fail
    long size = getpagesize() * 2;
    void *ptr = Mem_Alloc(size);
    
    // check if alloc fails
    if (ptr == NULL && m_error == E_NO_SPACE) {
        printf("No space left to allocate -- expected\n");
    }
    
    return 0;
}
