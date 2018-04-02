#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL -1

void bad_args_to_Mem_Init()
{
    printf("Testing: Bad args to Mem_Init()\n");
    printf("Try to Mem_Init(-6666)...\n");
    if (Mem_Init(-6666) != FAIL)
        exit(EXIT_FAILURE);
    if (m_error == E_BAD_ARGS)
        printf("Error: Bad Argument for Mem_Init.\n");
    printf("Try to Mem_Init(0)...\n");
    if (Mem_Init(0) != FAIL)
        exit(EXIT_FAILURE);
    if (m_error == E_BAD_ARGS)
        printf("Error: Bad Argument for Mem_Init.\n");
    printf("Try to Mem_Init(-666666669999999)...\n");    
    if (Mem_Init(-666666669999999) != FAIL)
        exit(EXIT_FAILURE);
    if (m_error == E_BAD_ARGS)
        printf("Error: Bad Argument for Mem_Init.\n");
    printf("Bad Args to Mem Init test success!\n");
    exit(EXIT_SUCCESS);
}

void main(void)
{
    bad_args_to_Mem_Init();
    exit(EXIT_SUCCESS);
}