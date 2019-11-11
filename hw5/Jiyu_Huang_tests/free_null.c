#include <stdlib.h>

#include "mem.h"

int main() {
    if (Mem_Init(8)) return EXIT_FAILURE;
    if (Mem_Free(NULL, 0)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
