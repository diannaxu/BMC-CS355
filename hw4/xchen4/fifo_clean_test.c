// Author: Paprika Chen
// Test if thread_libterminate() cleans the queue
// Right behavior: Only print "nothiing should be printed except this", no memory leaks

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAIL -1

void test() {
  printf("I shouldn't be printed.");
}

int main() {
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int t0, t1;
  thread_create(test, NULL, 0);
  thread_create(test, NULL, 0);

  printf("Nothing should be printed except this\n");
  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}