// Simple two threads FIFO
// Dianna xu

/* Expected output
thread 0 : 3
thread 1 : 3
thread 0 : 2
thread 1 : 2
thread 0 : 1
thread 1 : 1
done
*/
#include <stdio.h>
#include "userthread.h"

void test(void* arg) {
  int i = *(int *)arg;
  for (int j=3; j>0; j--) {
    printf("thread %d : %d\n", i, j) ;
    thread_yield() ;
  }
}

int main () {
  thread_libinit(FIFO);
  int t0, t1;
  int a0=0;
  int a1=1;
  t0=thread_create(test, &a0, 0) ;
  t1=thread_create(test, &a1, 0) ;
  thread_join(t0);
  thread_join(t1);
  printf("done\n") ;
  thread_libterminate();
  return 0 ;
}
