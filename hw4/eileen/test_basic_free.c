include "userthread.h"

int main() {
  printf("* Test basic memory frees *\n");
  printf("* Should not have any memory leaks when terminates *\n");

  int result = thread_libinit("LOL");
  thread_libterminate();
}
