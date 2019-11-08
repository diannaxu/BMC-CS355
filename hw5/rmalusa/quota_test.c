// QUOTA_TEST.C 
// Tests that the user is only allowed to allocate more memory when they haven't reached their quota. First, the user requests up to their quota, 
// and is denied further memory. But, after freeing some of the allocations they have, it is allowed. 
// Expected behavior: all assertions succeed. 

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "mem.h"

int main(){

	assert(Mem_Init(100) == 0);
	void* ptr1 = Mem_Alloc(30);
	assert(ptr1);
	void* ptr2 = Mem_Alloc(30);
	assert(ptr2);
	void* ptr3 = Mem_Alloc(40);
	assert(ptr3);

	// This request is not allowed
	void* ptr4 = Mem_Alloc(20);
	assert(!ptr4);

	// After freeing one of the 30-byte blocks, it is allowed 
	assert(Mem_Free(ptr2, 0) == 0);
	ptr4 = Mem_Alloc(20); 
	assert(ptr4);

	// But we still cannot request another 20 bytes, as that would put us at 110
	void* ptr5 = Mem_Alloc(20);
	assert(!ptr5);

	exit(EXIT_SUCCESS);

}
