/* 
    Author: Esther(Xinning) Fang
    Initialize with size of 1 page
*/
#include <sdtio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    int page_size = getpagesize();
    printf("page size is: %d\n", page_size);

    if (Mem_Init(page_size) == -1) {
        printf("Error when initializing.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump(); // One block with the size of page_size
    return EXIT_SUCCESS;
}