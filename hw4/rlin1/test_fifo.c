#include "userthread.h"
#include "Node.h"

void testfunc1(){
  printf("testfunc1\n");
}

void testfunc2(){
  printf("testfun2\n");
}


int main(){
  if (thread_libinit(SJF) == -1)
    exit(EXIT_FAILURE);
  int one = thread_create(testfunc1, NULL, 1);
  int two = thread_create(testfunc2, NULL, -1);
  int three = thread_create(testfunc2, NULL, 0);
  if (thread_join(two)<0) exit(EXIT_FAILURE);
  if (thread_join(one)<0) exit(EXIT_FAILURE);
  
  int four = thread_create(testfunc2, NULL, -1);
  if (thread_join(four)<0) exit(EXIT_FAILURE);
  if (thread_join(three)<0) exit(EXIT_FAILURE);

  if (thread_libterminate()<0) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
