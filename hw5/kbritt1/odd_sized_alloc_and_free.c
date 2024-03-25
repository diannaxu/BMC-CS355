#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Mem_Init(1);
    void * temp = Mem_Alloc(213); // expect the chunk to actually be 216    
    free(temp);
    Mem_Dump(); // should expect to see two headers both are free their size should sum up to 32 + 32 + size1 + size2 = getpagesize() 
    return EXIT_SUCCESS;
}