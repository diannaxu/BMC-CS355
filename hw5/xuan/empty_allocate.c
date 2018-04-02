#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define NUM_ALLOC 2000000
#define FREE_FREQ 100          // 1:100
#define COALESCE_FREQ 100000   // 1:100000
#define BYTE 8

int main(int argc, char const *argv[])
{
	printf("An empty size allocation. Could refuse allocation request or allocate a header.\n");
	Mem_Init(4000);
	Mem_Alloc(0);
  	Mem_Dump();

	return EXIT_SUCCESS;
}
