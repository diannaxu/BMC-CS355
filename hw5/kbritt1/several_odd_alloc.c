#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    Mem_Init(4096);
    void * temps[5];
    temps[0] = Mem_Alloc(1242);
    temps[1] = Mem_Alloc(1);
    temps[2] = Mem_Alloc(103);
    temps[3] = Mem_Alloc(491);
    temps[4] = Mem_Alloc(1921);
    for(int i =0; i < 5; i++){
    Mem_Free(temps[i],0);
    };
    printf("SUCCESS\n m_error = %d", m_error);
    return EXIT_SUCCESS;
}