/**
 * prempt_thread.c
 * Author: aahmed1
 * Date: 3/8/2024
 * 
 * Description:
 * Tests premption. The only way for thread 2 to enter is
 * if thread 1 is stopped and swapped with thread 2 
 *
 * Expected Result:
 * Entered thread 1
 * Created thread 2
 * Entered thread 2
 */
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"


void thread_two_print()
{
	printf("Entered thread 2\n");
	exit(0);
}

void thread_one_print()
{
	printf("Entered thread 1\n");
	
   int tid = thread_create(thread_two_print, NULL, 0);
	if (tid == -1) {
      printf("ERROR: Could not create thread.\n");
      exit(EXIT_FAILURE);
   }

	printf("Created thread 2\n");

	// The only way for thread 2 to be entered is 
	// if thread 1 is switched for  thread 2.
	while (1);
}

int main(void)
{
	if (thread_libinit(SJF) == -1) {
		printf("ERROR: Could not intitialize thread library.\n");
      exit(EXIT_FAILURE);
   }

	int tid = thread_create(thread_one_print, NULL, 0);
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