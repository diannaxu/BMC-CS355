#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mem.h"


int main(){
	Mem_Init(20000);
	void *ptr  = Mem_Alloc(2015);
    void *ptr1 = Mem_Alloc(4215);
    void *ptr2 = Mem_Alloc(5841);
    void *ptr3 = Mem_Alloc(3462);
    void *ptr4 = Mem_Alloc(1563);
    void *ptr5 = Mem_Alloc(2018);
	Mem_Dump();
	Mem_Free(ptr2, 0);
	Mem_Dump();
	Mem_Free(ptr4, 0);
	Mem_Dump();
	Mem_Free(ptr3, 2);
	Mem_Dump();
}
