/**
 * Author: aahmed1
 * Date: 3/24/2024
 * 
 * Description:
 * The program request many chunks of memory of 
 * varying sizes in order to fragment memory
 * and then tests if they coalesce properly
 *
 * Expected Result:
 * PASSED
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "mem.h"

#define N 15

int main() {
    // Initialize memory alloc
    if (Mem_Init(7000) == -1) {
        printf("ERROR: Could not Mem_Init\n");
        exit(EXIT_FAILURE);
    }

    int pointers[N];
    
    pointers[0] = (int*)Mem_Alloc(1);
    pointers[1] = (int*)Mem_Alloc(32);
    pointers[2] = (int*)Mem_Alloc(9);
    pointers[3] = (int*)Mem_Alloc(1024);
    pointers[4] = (int*)Mem_Alloc(7);
    pointers[5] = (int*)Mem_Alloc(98);
    pointers[6] = (int*)Mem_Alloc(11);
    pointers[7] = (int*)Mem_Alloc(2050);
    pointers[8] = (int*)Mem_Alloc(1);
    pointers[9] = (int*)Mem_Alloc(3);
    pointers[10] = (int*)Mem_Alloc(5);
    pointers[11] = (int*)Mem_Alloc(21);
    pointers[12] = (int*)Mem_Alloc(3000);
    pointers[13] = (int*)Mem_Alloc(10000);
    pointers[14] = (int*)Mem_Alloc(48);
   

    for (int i=0; i<N; i++){
        if (pointers[i] == NULL){
            printf("ERROR: Could not Mem_Alloc %d\n", i);
            exit(EXIT_FAILURE);
        }
    }


    for (int i=0; i<N-1; i++){
        if (Mem_Free((void*) pointers[i], 0) == -1){
            printf("ERROR: Could not Mem_Free %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (Mem_Free((void*) pointers[N-1], 1) == -1){
        printf("ERROR: Could not coalesce\n");
        exit(EXIT_FAILURE);
    }

    printf("PASSED\n");
    return 0;
}
