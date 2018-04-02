#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define REQ_SIZE 1000
#define ALLOC_SIZE_SML 20
#define ALLOC_SIZE_LAG 60
#define ALLOC_SIZE_MED 40


int main(){
	int result = Mem_Init(REQ_SIZE);
	assert (result == 0);

	void * ptr;
	void * ptr2;
	void * ptr3;

	printf("----------------Starts allocating the first 40 byte--------------\n");
	ptr = Mem_Alloc(ALLOC_SIZE_MED);
	assert(ptr != NULL);
	Mem_Dump();

	printf("----------------Starts allocating the second 60 byte--------------\n");
	ptr2 = Mem_Alloc(ALLOC_SIZE_LAG);
	assert(ptr2 != NULL);
	Mem_Dump();

	assert(((char *)ptr2 - (char *)ptr1) % 8 == 0);

	printf("----------------Starts freeing without coalescing--------------\n");

	result = Mem_Free(ptr, 0);
	assert(result == 0);
	Mem_Dump();

	result = Mem_Free(ptr2, 0);
	assert(result == 0);
	Mem_Dump();

	printf("-----Starts allocating the third 20 byte, should go into the 60 byte block-------\n");
	ptr = Mem_Alloc(ALLOC_SIZE_LAG);
	assert(ptr2 != NULL);
	Mem_Dump();

	result = Mem_Free(ptr3, 0);
	assert(result == 0);
	Mem_Dump();


	printf("Exit success!\n");
}