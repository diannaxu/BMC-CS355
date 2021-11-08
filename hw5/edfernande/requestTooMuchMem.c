// Elly Fernandez
// check that initalization works
// testing an alloc that is the same size as entire block
// check to make sure second block is not also allocated
// expected output is one pointer printed by Mem_Alloc and a null pointer
// output dependent on Mem_Dump() implementation
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mem.h"

int main(int argc, char** argv) {
    int status = Mem_Init(1024);
    assert(status == 0);
    Mem_Dump();
    int* intPtr = Mem_Alloc(1024);
    if(intPtr == NULL) {
        printf("NULL ptr\n");
    }
    intPtr = Mem_Alloc(2);
    assert(intPtr == NULL);
    Mem_Dump();
    return EXIT_SUCCESS;
}
