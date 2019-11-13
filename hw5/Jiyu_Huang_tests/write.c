#include <stdlib.h>

#include "mem.h"

int main() {
    if (Mem_Init(8)) return EXIT_FAILURE;
    char *p = Mem_Alloc(sizeof(char));
    if (!p) return EXIT_FAILURE;
    *p = 'a';
    if (*p != 'a') return EXIT_FAILURE;
    if (Mem_Free(p, 0)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
