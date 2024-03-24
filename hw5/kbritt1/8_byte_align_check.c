#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Mem_Init(1);
    int *temp = Mem_Alloc(80);
    if ((unsigned long)temp%8 != 0) {
        Mem_Free(temp,0);
        return EXIT_FAILURE;
    }//from github
    Mem_Free(temp,0);
    printf("SUCCESS\n");
    return EXIT_SUCCESS;
}