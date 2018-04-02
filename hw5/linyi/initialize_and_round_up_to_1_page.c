#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define REQ_SIZE 1000


int main(){

	int result = Mem_Init(REQ_SIZE);
	assert (result == 0);
	
	printf("Exit success!\n");
}