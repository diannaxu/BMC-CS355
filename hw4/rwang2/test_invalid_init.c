//Author: Rachel(Ruochun) Wang
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int main(void) {
  printf("Should print init failed.\n");
  if (thread_libinit(100) == -1){
    printf("Init Failed\n");
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
