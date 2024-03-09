/**
 * hello_thread.c
 * Author: aahmed1
 * Date: 3/8/2024
 * 
 * Description:
 * Simple hello world test to test the creation of a 
 * single thread and its return
 *
 * Expected Result:
 * Hello World! You passed test 1
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void hello_world(void *arg){
  int test = *((int *) arg);
	printf("Hello world! You passed test %d\n", test);
}

int main(void)
{

	int test  = 1;

	if (thread_libinit(FIFO) == -1) {
		printf("ERROR: Could not intitialize thread library.\n");
      exit(EXIT_FAILURE);
   }
	
	int tid = thread_create(hello_world, &test, 0);
	if (tid == -1) {
      printf("ERROR: Could not create thread.\n");
      exit(EXIT_FAILURE);
   }

	if (thread_join(tid) == -1) {
      printf("ERROR: Could not join thread.\n");
      exit(EXIT_FAILURE);
   }

	if (thread_libterminate() == -1) {
		printf("ERROR: Could not terminate thread library.\n");
      exit(EXIT_FAILURE);
   }

	return 0;
}