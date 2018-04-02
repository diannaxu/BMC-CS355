#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>


int main(){

	int result = Mem_Init(getpagesize());
	assert (result == 0);
	
	printf("Exit success!\n");
}