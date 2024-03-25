#include "mem.h"
#include <stdio.h>

int main() {
    int init_size = 4096;
    if (Mem_Init(init_size) == -1) {
        return -1;
    }

    int blockSize = 1024;
    void *ptrs[4];
    int i;
    for (i = 0; i < 4; i++) {
        ptrs[i] = Mem_Alloc(blockSize);
        if (ptrs[i] == NULL) {
            break;
        }
    }

    void *ptr = Mem_Alloc(blockSize);
    if (ptr == NULL && m_error == E_NO_SPACE) {
        printf("No space left to allocate test passed\n");
    } else {
        printf("No space left to allocate test failed\n");
    }

    for (int j = 0; j < i; j++) {
        if (ptrs[j] != NULL) {
            Mem_Free(ptrs[j], 1);
        }
    }

    return 0;
}
