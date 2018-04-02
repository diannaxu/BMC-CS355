#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define REQ_SIZE 80
#define ALLOC_SIZE 1000


int main(){
	int result = Mem_Init(REQ_SIZE);
	assert (result == 0);

	void * ptr;

	ptr = Mem_Alloc(ALLOC_SIZE);
	assert(ptr == NULL);
	Mem_Dump();

	printf("Exit success!\n");
}