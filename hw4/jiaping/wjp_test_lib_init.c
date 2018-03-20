#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"


int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);


  printf("Test case for libinit and libterminate\n");
  printf("Print \"You did it!\" on success.\n");


  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  printf("You did it!\n");
  exit(EXIT_SUCCESS);
}