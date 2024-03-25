// Test 14: try to free a NULL pointer
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(4096) == FAIL) {
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }
    
    if(Mem_Free(NULL, 0) == FAIL){
        if (m_error == E_BAD_POINTER){
            printf("Test passed \n");
        }
        else{
            printf("Test failed \n");
        }
        exit(EXIT_FAILURE);
    }

    Mem_Dump();
    
    return 0;
}
