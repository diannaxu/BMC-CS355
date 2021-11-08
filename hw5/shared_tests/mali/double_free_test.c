#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mem.h"


int main(){
	Mem_Init(20000);
	void *ptr  = Mem_Alloc(2015);
	Mem_Dump();
	Mem_Free(ptr, 0);
	Mem_Dump();
	Mem_Free(ptr, 0);
	Mem_Dump();
}
