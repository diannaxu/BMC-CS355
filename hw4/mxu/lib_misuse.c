#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void test(void* trash) {
  printf("hello, world\n");
}
/*
  a very simple basic fifo test to test misuse of thread library.
  You can also comment all the thread_create and thread_join
  to test whether your thread_libinit and thread_libterminate works
*/

int main(int args, char** argv) {
  printf("all create will fail but nothing weird will happen\n");
  int tid1 =  thread_create(test,NULL,0);
  int tid2 =  thread_create(test,NULL,0);
  thread_join(tid1);
  if(thread_libinit(FIFO) == 0)
    printf("Ya ho!\n");
  else
    printf("Sad.. I fail\n");
  printf("now it should work correctly\n");
  int tid3 =  thread_create(test,NULL,0);
  int tid4 =  thread_create(test,NULL,0);
  thread_join(tid3);
  //cout << "size of queue is now: " << fifoq.size() << endl;
  if(thread_libterminate() == 0)
    printf("lib term Ya ho!\n");
  else
    printf("Sad.. I fail to term\n");

  //mythread* kk = fifoq.front();
  //makecontext(kk->uc, test, 0);
  //setcontext(kk->uc);
  return 0;
}