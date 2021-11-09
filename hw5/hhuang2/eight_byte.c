/*
 * Author: Haosong Huang
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

int main()
{
    /* Mem_Init test */
    int heap = Mem_Init(8);
    printf("You should observe that the allocated chunk has size 8\n");
    void* a  = Mem_Alloc(8);
    void* b  = Mem_Alloc(1);
    void* c  = Mem_Alloc(2);
    void* d  = Mem_Alloc(3);
    Mem_Dump();
    printf("You should observe two 8 byte freed chunks and two 8 bytes allocated chunk and a big free chunk\n");
    Mem_Free(c,0);
    Mem_Free(a,0);
    Mem_Dump();
    return EXIT_SUCCESS;
}