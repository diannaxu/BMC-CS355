#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM_ALLOC 8192
#define FAIL -1

void memory_can_be_written_after_allocation()
{
    printf("Test: Memory can be written after allocation\n");
    printf("----Mem_Init(8192)----\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("----Mem_Alloc(32*sizeof(char))----\n");
    char *ptr = (char *)Mem_Alloc(32*sizeof(char));
    char *buf = "OS is Hard!";
    printf("The string buf is %s.\n\n",buf);
    printf("----strncpy(ptr,buf,32*sizeof(char)):----\n");
    printf("The string \"%s\" should be written into ptr.\n", buf);
    strncpy(ptr,buf, 32*sizeof(char));
    printf("The ptr is %s.\n\n",ptr);
    if (ptr == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("----Mem_Free(ptr, 1)----\n");
    if (Mem_Free(ptr, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    exit(EXIT_SUCCESS);
}

void main(void)
{
    memory_can_be_written_after_allocation();
    exit(EXIT_SUCCESS);
}
