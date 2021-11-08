#include <stdlib.h>
#include <unistd.h>
#include "mem.h"

int main()
{
    int result = Mem_Init(-6000);
    if (result == -1)
    {
        printf(">:( NO NEGATIVE NUMBERS\n");
    }
    int result2 = Mem_Init(0);
    if(result2 == -1)
    {
        printf(">:( SIZE MUST BE GREATER THAN ZERO\n");
        exit(EXIT_FAILURE);
    }

    printf("BOTH WORKED >:( THIS SHOULD NOT HAPPEN\n");
    exit(EXIT_SUCCESS);
}