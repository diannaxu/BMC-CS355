#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mem.h"


int main(){
	Mem_Init(20000);
	void *ptr  = Mem_Alloc(2015);
	Mem_Dump();
    void *ptr1 = Mem_Alloc(4215);
	Mem_Dump();
    void *ptr2 = Mem_Alloc(1841);
	Mem_Dump();
    void *ptr3 = Mem_Alloc(3462);
	Mem_Dump();
    void *ptr4 = Mem_Alloc(1563);
	Mem_Dump();
    void *ptr5 = Mem_Alloc(2018);
	Mem_Dump();
}
