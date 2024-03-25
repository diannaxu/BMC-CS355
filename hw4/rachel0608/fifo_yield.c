/* Expected output
Thread 1 running
Thread 2 running
Thread 1 running
Thread 2 running
Thread 1 running
Thread 2 running
Thread 1 running
Thread 2 running
Thread 1 running
Thread 2 running
*/

#include <stdio.h>
#include "usethread.h"

void yield_thread(void *arg) {
    int *tid = (int *)arg;
    for (int i = 0; i < 5; ++i) {
        printf("Thread %d running\n", *tid);
        thread_yield();
    }
}

int main() {
    thread_libinit(FIFO);
    int a0 = 1;
    int a1 = 2;
    int tid1 = thread_create(yield_thread, &a0, 0);
    int tid2 = thread_create(yield_thread, &a1, 0);

    thread_join(tid1);
    thread_join(tid2);

    thread_libterminate();
    return 0;
}
