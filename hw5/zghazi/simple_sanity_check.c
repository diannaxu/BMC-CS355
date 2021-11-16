/*
 * Author: Zaynab Ghazi
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

int main()
{
    /* Mem_Init test */
    int heap = Mem_Init(sizeof(int) * 777);
    assert(heap == 0);
    //test failed duplicate call
    int heap_duplicate = Mem_Init(sizeof(int) * 7);
    assert(heap_duplicate == -1);

    /* Mem_Alloc test */
    //ODD ALLOC
    int *ptr;
    ptr = (int *)Mem_Alloc(77);
    //check pointer correctness
    assert(ptr != NULL);
    assert(((long)ptr) % 8 == 0);
    //check pointer is writable
    for(int i=0; i < 10; i++) *(ptr+i) = i;
    for(int i=0; i < 10;i++) printf("memory at %p is writable: %d should equal %d\n", ptr+i, *(ptr+i),i);
     Mem_Dump();
    int free_result = Mem_Free(ptr, 0);
    assert(free_result == 0);
    //FREE free'd pointer
    int invalid_free = Mem_Free(ptr,0);
    assert(invalid_free == -1);

    //simple 8 byte allocation
    int *ptr_;
    ptr_= (int *)Mem_Alloc(8);
    //check pointer correctness
    assert(ptr_ != NULL);
    assert(((long)ptr_) % 8 == 0);

    //check over-memory 
    int *ptr_max;
    ptr_max= (int *)Mem_Alloc(20000);
    //check pointer correctness
    assert(ptr_max == NULL);
    //check right error code
    assert(m_error == E_NO_SPACE);

    //cleanup
    int free = Mem_Free(ptr_, 0);
    assert(free ==0);
    Mem_Dump();
    return EXIT_SUCCESS;
}
