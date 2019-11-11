#include <stdlib.h>

#include "mem.h"

int main() {
    if (Mem_Init(9)) return EXIT_FAILURE;
    void *p = Mem_Alloc(1), *q = Mem_Alloc(1);
    if (!p || !q) return EXIT_FAILURE;
    if ((long) p % 8 || (long) q % 8) return EXIT_FAILURE;
    if (Mem_Free(p, 0) || Mem_Free(q, 0)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
