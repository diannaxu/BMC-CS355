/*
    Author: Esther(Xinning) Fang
    Bad args for Mem_Init() with a negative sizeOfRegion
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    printf("------------Mem_Init(-1024)------------\n");
    if (Mem_Init(-1024) == -1) {
        printf("Success: sizeOfRegion is negative and Mem_Init() failed.\n");
    } else {
        printf("Should have returned -1.\n");
    }

    return EXIT_SUCCESS;
}
