#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define REQ_SIZE 1000
#define ALLOC_SIZE 80


int main(){
	int result = Mem_Init(REQ_SIZE);
	assert (result == 0);

	void * ptr;
	void * ptr2;

	printf("----------------Starts allocating the first 8 byte--------------\n");
	ptr = Mem_Alloc(ALLOC_SIZE);
	assert(ptr != NULL);
	Mem_Dump();

	printf("----------------Starts allocating the second first 8 byte--------------\n");
	ptr2 = Mem_Alloc(ALLOC_SIZE);
	assert(ptr2 != NULL);
	Mem_Dump();

	assert(((char *)ptr2 - (char *)ptr1) % 8 == 0);

	printf("----------------Starts freeing--------------\n");

	result = Mem_Free(ptr, 0);
	assert(result == 0);
	Mem_Dump();

	result = Mem_Free(ptr2, 0);
	assert(result == 0);
	Mem_Dump();

	printf("Exit success!\n");
}