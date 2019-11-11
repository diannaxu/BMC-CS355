#include <stdlib.h>

#include "mem.h"

int main() {
    if (Mem_Init(getpagesize() - 1)) return EXIT_FAILURE;
    void *p = Mem_Alloc(getpagesize() - 1);
    if (!p) return EXIT_FAILURE;
    if (Mem_Free(p, 0)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
