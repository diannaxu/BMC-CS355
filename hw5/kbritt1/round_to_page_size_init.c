#include "../mem.h"
#include <unistd.h>
#include <stdlib.h> 

int main(){
    long pg =  getpagesize()- 100;
	printf("%d\n",Mem_Init(pg));
    Mem_Dump(); //expectect mapped region to be 1 page size + padding
    return EXIT_SUCCESS;
}