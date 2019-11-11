#include <stdlib.h>

#include "mem.h"

int main() {
    if (Mem_Init(9)) return EXIT_FAILURE;
    void *p = Mem_Alloc(1), *p1 = p;
    if (Mem_Free(p, 0)) return EXIT_FAILURE;
    p = Mem_Alloc(1);
    if (p1 == p) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
