#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Mem_Init(1);
    void * temps[5];
    for (int i = 0; i < 5; i++){
        temps[i] = Mem_Alloc(i+1*30);
    }
    for(int i =0; i < 5; i++){
    if ((unsigned long)temps[i]%8 != 0) {
        Mem_Free(temps[i],0);
        return EXIT_FAILURE;
    }//from github
    Mem_Free(temps[i],0);
    };
    printf("SUCCESS\n");
    return EXIT_SUCCESS;
}