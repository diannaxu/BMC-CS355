/**
 * thread_yield.c
 * Author: aahmed1
 * Date: 3/8/2024
 * 
 * Description:
 * Tests the creation and yielding of multiple threads
 *
 * Expected Result:
 * Thread 1
 * Thread 2
 * Thread 3
 */
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void make_thread_three()
{
   int y = thread_yield();
   if (y == -1) {
      printf("ERROR: Could not yield.\n");
      exit(EXIT_FAILURE);
   }

	printf("Thread 3\n");	
}

void make_thread_two()
{
   int tid = thread_create(make_thread_three, NULL, 0);
	if (tid == -1) {
      printf("ERROR: Could not create thread.\n");
      exit(EXIT_FAILURE);
   }

   int y = thread_yield();
   if (y == -1) {
      printf("ERROR: Could not yield.\n");
      exit(EXIT_FAILURE);
   }

	printf("Thread 2\n");	
}


void make_thread_one()
{
   int tid = thread_create(make_thread_two, NULL, 0);
	if (tid == -1) {
      printf("ERROR: Could not create thread.\n");
      exit(EXIT_FAILURE);
   }

	int y = thread_yield();
   if (y == -1) {
      printf("ERROR: Could not yield.\n");
      exit(EXIT_FAILURE);
   }

	printf("Thread 1\n");
	
   y = thread_yield();
   if (y == -1) {
      printf("ERROR: Could not yield.\n");
      exit(EXIT_FAILURE);
   }
}

int main(void)
{
	if (thread_libinit(FIFO) == -1) {
		printf("ERROR: Could not intitialize thread library.\n");
      exit(EXIT_FAILURE);
   }

	int tid = thread_create(make_thread_one, NULL, 0);
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