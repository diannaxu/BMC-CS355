/* 
    Author: Esther(Xinning) Fang
    Given two free chunks, check if Mem_Alloc() takes the chunk with the largest size
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(4096) == -1) {
        printf("Error when initilizing.\n");
        exit(EXIT_FAILURE);
    } 

    void *ptr1 = Mem_Alloc(1024);
    if (ptr1 == NULL) {
        printf("Error during allocation.\n");
        exit(EXIT_FAILURE);
    } 
    Mem_Free(ptr1, 0);
    Mem_Dump();

    void *ptr2 = Mem_Alloc(100);
    if (ptr2 == NULL) {
        printf("Error during allocation.\n");
        exit(EXIT_FAILURE);
    } 
    Mem_Dump(); // Should take the second chunk
    return EXIT_SUCCESS;
}
