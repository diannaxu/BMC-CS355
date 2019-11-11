## HW5 Test Suite

### alignment.c
- Purpose: Testing for 8-byte alignment test using Mem_Dump and mod on pointer address.
- Expected Output: Mem_Dump output should show 8-byte alignment, and pointer modular
arithmetic should yield 0 for 8-byte alignment

### allocation.c
- Purpose: Make sure allocations of various sizes are 8-byte aligned
- Expected Result: Mem_Dump output should still be 8-byte aligned, and pointer modular arithmetic should still yield 0 for 8-byte alignment

### bad-args-mem-init.c
- Purpose: see what happens when we send bad args to mem_init
- Expected Result: Mem init should return FAILURE because of bad args

### coalesce.c
- Purpose: make sure memory coalesces
- Expected: Mem_Dump will show that there is a single block of memory after all the frees

### few-aligned-allocations.c
- Purpose: Allocate a few blocks and show they are still aligned
- Expected Result: Mem_Dump output should be 8-byte aligned, pointer arithmetic should show alignment, mod 8 on ptr should yield zero

### misuse-multiple-init-calls.c
- Purpose: Try to call init multiple times
- Expected Result: print "init failed" for every time mem_init is called after the first time ("init failed" prints 4 times)

### odd-alignment-blocks.c
- Purpose: Allocate a odd size blocks and ensure alignment
- Expected Result: Mem_Dump output should be 8-byte aligned, pointer arithmetic should show alignment, mod 8 on ptr should yield zero

### wf.c
- Purpose: make sure allocation occurs according to worst fit
- Expected: Mem_Dump will show that worst fit allocation is used (always goes to the biggest block even when there's a better fit available)

### simple-allocation-free.c   
- Purpose: testing simple allocation and free
- Expected Result: one contiguous block at end of test and block allocated should be freed

### simple-aligned-alloc-free.c
- Purpose: testing simple aligned byte allocation and free
- Expected Result: one contiguous block at end of test and block allocated should be freed, normal alignment

### odd-aligned-alloc-free.c
- Purpose: testing odd aligned byte allocation and free
- Expected Result: one contiguous block at end of test and block allocated should be freed, normal alignment

### one-page.c
- Purpose: testing one page allocation, freeing
- Expected Result: one contiguous block at end of test and block allocated should be freed, normal alignment, should be able to allocate pagesize

### round-one-page.c
- Purpose: initializing and rounding up to one page
- Expected Result: one contiguous block at end of test and the free block should be the size of page size

### no-space.c
- Purpose: testing what happens when we run out of space
- Expected Result: E_NO_SPACE (1) is the value of m_error because we run out of space

### free-null.c
- Purpose: Testing trying to free null pointer
- Expected Output: should coalesce if coalesce is 1, otherwise do not try to free nullptr

### writeable.c
- Purpose: Checks if memory is writeable
- Expected Output: After string is written to memory allocated, if it prints that string, the test is successful.
