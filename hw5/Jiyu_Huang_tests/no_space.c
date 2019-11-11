#include <stdlib.h>

#include "mem.h"

int main() {
    if (Mem_Init(8)) return EXIT_FAILURE;
    void *p = Mem_Alloc(8);
    if (!p) return EXIT_FAILURE;
    void *q = Mem_Alloc(1);
    if (q) return EXIT_FAILURE;
    if (Mem_Free(p, 0)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
