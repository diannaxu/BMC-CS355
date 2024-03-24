#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
    Mem_Init(4096);
    void * temp = Mem_Alloc(8);
    free(temp);
    Mem_Dump(); // should excpect to see two headers both are free their size should sum up to HS + HS + size1 + size2 = 4096
    return EXIT_SUCCESS;
}