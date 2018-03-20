#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAILURE -1

void foo() {
	printf("Woo!\n");
}

int main(void) {
  printf("Testing some misuses of threads\n");
  printf("This assumes that the priority queue range is from -1 to 1\n");
  printf("because it tests adding a thread with priority 100\n");
  printf("On success, it prints 'Woo!', does not crash, and does not cause any memory leaks\n"); 
  
  int tidx = thread_create(foo, NULL, 0);
  if (tidx != -1) 
  	exit(EXIT_FAILURE);

  thread_libterminate();

  if (thread_libinit(PRIORITY) == FAILURE)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo, NULL, 100);
  if (tid1 == -1)
  	exit(EXIT_FAILURE);

  if (thread_join(tid1) == -1)
  	exit(EXIT_FAILURE);

  if (thread_libterminate() == FAILURE)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
