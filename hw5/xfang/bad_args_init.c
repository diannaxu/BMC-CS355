/* 
    Author: Esther(Xinning) Fang
    Bad args for Mem_Init(), including sizeOfRegion less than 0 and multiple calls to Mem_Init()
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    printf("------------Mem_Init(-1024)------------\n");
    if (Mem_Init(-1024) == -1) {
        printf("Bag args: sizeOfRegion is negative.\n");
    } else {
        printf("Should return with error.\n");
    }

    printf("------------Multiple calls to Mem_Init()------------\n");
    if (Mem_Init(1024) == -1) {
        printf("Error when initilizing.\n");
        exit(EXIT_FAILURE);
    } 
    if (Mem_Init(1024) == -1) {
        printf("Success: Error when initilizing.\n");
    } else {
        printf("Should return with error.\n");
    } 

    return EXIT_SUCCESS;
}