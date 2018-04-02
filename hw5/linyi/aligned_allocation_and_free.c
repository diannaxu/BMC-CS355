#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define REQ_SIZE 50
#define ALLOC_SIZE 1000
#define ALLOC_AMOUNT 10

int main(){
	int result = Mem_Init(REQ_SIZE);
	assert (result == 0);

	void **array = malloc(sizeof(void*) * ALLOC_AMOUNT);

	printf("----------------Starts allocating--------------\n");
	for (int i = 0; i < ALLOC_AMOUNT; i++){
		array[i] = Mem_Alloc(ALLOC_SIZE);
		assert(array[i] == NULL);
		Mem_Dump();
	}

	printf("Exit success!\n");
}