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

	printf("----------------Starts allocating the first 8 byte--------------\n");
	ptr = Mem_Alloc(ALLOC_SIZE);
	assert(ptr != NULL);
	Mem_Dump();


	strcpy(ptr0, "Hello!");

  	printf("%s\n", ptr0);

	printf("----------------Starts freeing--------------\n");

	result = Mem_Free(ptr, 0);
	assert(result == 0);
	Mem_Dump();

	printf("Exit success!\n");
}