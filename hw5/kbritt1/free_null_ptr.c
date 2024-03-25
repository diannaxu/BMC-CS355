#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 0
int main(){
    Mem_Init(1);   
    if (SUCCESS == Mem_Free(NULL, NULL)) {printf("SUCCESS"); return EXIT_SUCCESS;}
    return EXIT_FAILURE;
}