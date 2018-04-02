
#include <stdio.h>
#include "uthread.h"

long count = 0;

void thread1() {
    int i;

    for (i = 0; i < 10; ++ i) {
        count += 1;
        thread_yield();
    }
}

void thread2() {
    int i ;

    for (i = 0; i < 10; ++ i) {
        count *= 2;
        thread_yield();
    }
}

void main() {

  printf("---------\n");
  printf("A FIFO test with yeild\n");
  printf("Should print -2046-  on success.\n");
  printf("The threads should be scheduled in-order, sicne it is a FIFO scheduler\n");
  printf("---------\n");

  if (thread_libinit(FIFO) == -1) {
    exit(EXIT_FAILURE);
  }

  int a, b;

  a = thread_create(thread1, NULL, 0);
  b = thread_create(thread2, NULL, 0);

  thread_join(a);
  thread_join(b);

  printf("%ld\n", count);

  if (thread_libterminate() == -1) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
