#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mem.h"


int main(){
	Mem_Init(20000);
	void *ptr  = Mem_Alloc(2015);
	Mem_Dump();
	Mem_Free(ptr+20, 0);
	printf("m_error: %d",m_error);
	Mem_Dump();
}
