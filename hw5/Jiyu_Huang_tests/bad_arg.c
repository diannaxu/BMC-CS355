#include <stdlib.h>
#include <unistd.h>

#include "mem.h"

int main() {
    if (!Mem_Init(0)) return EXIT_FAILURE;
    if (!Mem_Init(-1)) return EXIT_FAILURE;
    if (Mem_Init(getpagesize())) return EXIT_FAILURE;
    if (!Mem_Init(getpagesize())) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
