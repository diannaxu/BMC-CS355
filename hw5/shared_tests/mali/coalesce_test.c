#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mem.h"


int main(){
	Mem_Init(20000);
	void *ptr  = Mem_Alloc(1000);
    void *ptr2 = Mem_Alloc(1000);
    void *ptr3 = Mem_Alloc(1000);
    void *ptr4 = Mem_Alloc(1000);
    void *ptr5 = Mem_Alloc(1000);
	Mem_Dump();
	Mem_Free(ptr2, 0);
	Mem_Dump();
	Mem_Free(ptr4, 0);
	Mem_Dump();
	Mem_Free(ptr3, 1);
	Mem_Dump();
}
