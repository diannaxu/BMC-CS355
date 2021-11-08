#include <stdlib.h>
#include <unistd.h>
#include "mem.h"

int main()
{
    int result = Mem_Init(6000);
    if (result == -1)
    {
        printf("FIRST TIME FAILED (should not happen)\n");
        exit(EXIT_FAILURE);
    }
    int result2 = Mem_Init(6000);
    if(result2 == -1)
    {
        printf("SECOND TIME FAILED (this should happen)\n");
        exit(EXIT_FAILURE);
    }

    printf("BOTH TIME WORKED >:( THIS SHOULD NOT HAPPEN\n");
    exit(EXIT_SUCCESS);
}