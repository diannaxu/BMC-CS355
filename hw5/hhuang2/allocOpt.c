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
    printf("In normal order we put allocated at the bottom and free at the top");
    void* a  = Mem_Alloc(8);
    Mem_Dump();
    printf("Now free the last allocated chunk to create FF");
    Mem_Free(a,0);
    Mem_Dump();
    printf("You should observe that the order is AFF instead of FAA for the new allocation\n");
    Mem_Alloc(8);
    Mem_Dump();
    return EXIT_SUCCESS;
}