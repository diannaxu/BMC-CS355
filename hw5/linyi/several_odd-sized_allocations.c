#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define REQ_SIZE 2000
#define ALLOC_SIZE 49
#define ALLOC_AMOUNT 10

int main(){
	int result = Mem_Init(REQ_SIZE);
	assert (result == 0);

	void **array = malloc(sizeof(void*) * ALLOC_AMOUNT);

	printf("----------------Starts allocating--------------\n");
	for (int i = 0; i < ALLOC_AMOUNT; i++){
		array[i] = Mem_Alloc(ALLOC_SIZE);
		assert(array[i] != NULL);
		Mem_Dump();
	}

	printf("----------------Starts freeing--------------\n");
	for (int i = 0; i < ALLOC_AMOUNT; i++){
		result = Mem_Free(array[i], 0);
		assert(result == 0);
		Mem_Dump();
	}

	free(array);
	printf("Exit success!\n");
}