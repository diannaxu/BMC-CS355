/*
    Author: Esther(Xinning) Fang
    Initialize with size that rounds up to the size of 1 page
    When Mem_Dump(), the size of the allocated block should be page_size

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    int page_size = getpagesize();
    printf("page size is: %d\n", page_size);

    printf("Calling Mem_Init(page_size - 1)\n");
    if (Mem_Init(page_size - 1) == -1) {
        printf("Error when initializing.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump(); // One block with the size of page_size
    return EXIT_SUCCESS;
}
