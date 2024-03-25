/**
 * Author: aahmed1
 * Date: 3/24/2024
 * 
 * Description:
 * checks that memory can be written to
 * and read from after allocation
 *
 * Expected Result:
 * 0, 1, 2, ... N-1
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "mem.h"

#define N 36

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init\n");
        exit(EXIT_FAILURE);
    }

    int *ptr = (int*)Mem_Alloc(N);
    if (ptr == NULL){
        printf("ERROR: Could not Mem_Alloc\n");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<N; i++){
        ptr[i] = i;
    }

    for (int i=0; i<N; i++){
        printf("%d, ", ptr[i]);
    }
    printf("\n");

    if (Mem_Free(ptr, 1) == -1 ){
        printf("ERROR: Could not Mem_Free\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}