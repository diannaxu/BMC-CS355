#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h> 
#include <stdbool.h>

#define PAGE_SIZE 4096
#define NUM_ALLOC 8192
#define FAIL -1
#define TRUE 1
#define FALSE 0

void test_bad_args_to_mem_init() {
    printf("Test: Bad args to Mem_Init()\n");
    if (Mem_Init(0) == FAIL) {
        printf("Success: Mem_Init() failed with bad arguments!\n");
        if (m_error == E_BAD_ARGS)
            printf("Error: Bad arguments to Mem_Init()\n");
    }
}

int main(){
    test_bad_args_to_mem_init();
    return 0;
}