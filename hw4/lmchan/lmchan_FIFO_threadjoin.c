
#include <stdio.h>
#include "uthread.h"

void sky() {
  printf("Hello, sky!\n");
}

void ground() {
  printf("Hello, ground!\n");
}

void main() {

  printf("---------\n");
  printf("A FIFO test with yeild\n");
  printf("Should print -hello, sky!- then -hello,ground!-  on success.\n");
  printf("The threads should be scheduled in-order, sicne it is a FIFO scheduler\n");
  printf("---------\n");

  if (thread_libinit(FIFO) == -1) {
    exit(EXIT_FAILURE);
  }

  int a, b, c;

  a = thread_create(sky, NULL, 0);

  if(thread_join(a) != 0) {
    printf("thread_join(a) did not work\n");
  }

  b = thread_create(ground, NULL, 0);

  if(thread_join(b) != 0) {
    printf("thread_join(b) did not work\n");
  }


  if (thread_libterminate() == -1) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
