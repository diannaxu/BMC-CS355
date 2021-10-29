#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"
#ifndef NULL
#define NULL (0)
#endif


void horoscope(void* gemini_men) {
  printf("Your daily horoscope...\n");
}
/*
  a very simple basic sjf test.
  See whether sjf's priority queue works as expected.
*/

int main() {

  if(thread_libinit(FIFO) == 0)
  {
    printf("Thread Library successfuly created !\n");
  }else
  {
    printf("ERROR: THREAD LIBRARY CANNOT BE CREATED\n");
  }
  
  printf("Logger should show that thread 1 executes first\n");
  int one =  thread_create(horoscope,NULL,0);
  int two =  thread_create(horoscope,NULL,0);


  if(thread_join(one) < 0)
  {
    exit(EXIT_FAILURE);
  }
  if(thread_join(two) < 0)
  {
    exit(EXIT_FAILURE);
  }

  if(thread_libterminate() == 0)
  {
    printf("Thread Library is gone !\n");
  }else
  {
    printf("ERROR: CANNOT DELETE THREAD LIBRARY\n");
  }
  return 0;

}