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

int m_error;

int main(int argc, char const *argv[])
{
	printf("Allocation beyond requested size. Should refuse allocation request and set error.\n");
	Mem_Init(4000);
	Mem_Alloc(4096-32*2);
	Mem_Alloc(8);
  	Mem_Dump();

  	if(m_error == E_NO_SPACE)
  		printf("ERROR DETECTED: no space \n");


	return EXIT_SUCCESS;
}
