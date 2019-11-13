/* 
    Author: Esther(Xinning) Fang
    Simple 8-byte allocation and free
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(4096) == -1) {
        printf("Error when initializing.\n");
    }

    // 8-byte allocation  
    void *ptr1 = Mem_Alloc(8);
    if (ptr1 == NULL) {
        printf("Error during 8-byte allocation.\n");
        exit(EXIT_FAILURE);
    } 

    Mem_Dump(); 
    if (Mem_Free(ptr1, 0) == =1) {
        printf("Error when freeing the 8-byte allocation.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();

    return EXIT_SUCCESS;
}