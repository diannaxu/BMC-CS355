// C file for testing:
// 5. bad args to Mem_Init()
// 11. initialize with size of 1 page
// extra. bad args to Mem_()
// 14. try to free a NULL pointer (2 cases)
// @author Li Fan

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

int main(){
    int result = Mem_Init(-1);
    assert(result == -1);
    assert(m_error == E_BAD_ARGS);

    result = Mem_Init(4096);    // i printed number of pages(return value of mmap) in my library function (Init) to check the roundup
    assert(result == 0);
    printf("PASSED\n");
    return 0;
}