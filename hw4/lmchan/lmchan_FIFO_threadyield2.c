
#include <stdio.h>
#include "uthread.h"

long count = 0;
long count2 = 0;

void thread1() {
    int i;

    for (i = 0; i < 100; ++ i) {
        count += 1;
        thread_yield();
        count2 += 3;
    }
}


void main() {

  printf("---------\n");
  printf("A FIFO test with yeild that focuses on only one thread running\n");
  printf("Should print -100 300- on success.\n");
  printf("The threads should be scheduled in-order, sicne it is a FIFO scheduler\n");
  printf("---------\n");

  if (thread_libinit(FIFO) == -1) {
    exit(EXIT_FAILURE);
  }

  int a;

  a = thread_create(thread1, NULL, 0);

  thread_join(a);

  printf("%ld %ld\n", count, count2);

  if (thread_libterminate() == -1) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
