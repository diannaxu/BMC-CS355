/**
 * Author: aahmed1
 * Date: 3/24/2024
 * 
 * Description:
 * tries to free null pointers
 *
 * Expected Result:
 * PASSED
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "mem.h"

#define N 64

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init\n");
        exit(EXIT_FAILURE);
    }

    if (Mem_Free(NULL, 1) == -1 ){
        printf("ERROR: Could not Mem_Free NULL\n");
        exit(EXIT_FAILURE);
    }

    void *ptr = Mem_Alloc(N);
    if (ptr == NULL){
        printf("ERROR: Could not Mem_Alloc\n");
        exit(EXIT_FAILURE);
    }

    if (Mem_Free(ptr, false) == -1 ){
        printf("ERROR: Could not Mem_Free\n");
        exit(EXIT_FAILURE);
    }

    if (Mem_Free(ptr, 1) == -1 ){
        printf("ERROR: Could not Mem_Free Twice\n");
        exit(EXIT_FAILURE);
    }

    printf("PASSED\n");
    return 0;
}