/*
    Author: Esther(Xinning) Fang
    Bad args for Mem_Init(), multiple calls of Mem_Init().
    Should return -1 for the second call
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    printf("-------------------Mem_Init(4096)-------------------\n");
    if (Mem_Init(4096) == -1) {
        printf("Bag args: sizeOfRegion is negative.\n");
    }

    printf("------------Multiple calls to Mem_Init()------------\n");
    if (Mem_Init(4096) == -1) {
        printf("Success: Error when initilizing.\n");
    } else {
      printf("Should have returned -1.\n");
      exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}
