// Give thread_libinit() an integer input not corresponding with any of
// the policies (which are FIFO = 0, SJF = 1, and PRIORITY = 2)
// and make sure it's returning -1, indicating that initialization has failed
// Victor Nault

#include <stdio.h>
#include "userthread.h"

#define SUCCESS 0
#define FAIL -1
#define INVALID_POLICY = 3

int main() {
    int init_ret_val;
    init_ret_val = thread_libinit(INVALID_POLICY);
    printf("Expected output of thread_libinit(): %d\n", FAIL);
    printf("Actual output of thread_libinit(): %d\n", init_ret_val);
}
