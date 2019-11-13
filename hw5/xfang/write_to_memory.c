/*
    Author: Esther(Xinning) Fang
    Test to check if allocated memory is writable
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(1024) == -1) {
        printf("Error when initilizing.\n");
        exit(EXIT_FAILURE);
    }
    int *ptrs[3];
    for (int i = 0; i < 3; i++) {
        ptrs[i] = Mem_Alloc(sizeof(int));
        if (ptrs[i] == NULL) {
            printf("Error during allocation.\n");
            exit(EXIT_FAILURE);
        }
        *ptrs[i] = i;
    }
    Mem_Dump();
    for (int j = 0; j < 3; j++) {
        printf("%d is written to memory location %p.\n", *ptrs[j], ptrs[j]);
        Mem_Free(ptrs[j], 0);
    }
    Mem_Dump();

    return EXIT_SUCCESS;
}