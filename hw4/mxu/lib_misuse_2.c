#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"


void misuse(void* trash) {
  thread_libterminate();
}
/*
  a very simple basic fifo test to test misuse of thread library.
  here,we will let thread calling lib terminate
*/

int main(int args, char** argv) {
  if(thread_libinit(FIFO) == 0)
    printf("Ya ho!\n");
  else
    printf("Sad.. I fail\n");
  printf("now it should work correctly\n");
  int tid3 =  thread_create(misuse,NULL,0);
  int tid4 =  thread_create(misuse,NULL,0);
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