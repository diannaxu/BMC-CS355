#include "userthread.h"
#include <stdio.h>

int main() {
  printf("* Test basic memory frees *\n");
  printf("* Should not have any memory leaks when terminates *\n");
  int false = 10;
  int result = thread_libinit(false);
  thread_libterminate();
}
