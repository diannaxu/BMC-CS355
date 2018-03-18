
#include "userthread.h"
#include <stdio.h> 
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>


void func(){
  for(int i=0;i<10;i++)
  	poll(NULL, 0, 20);
}


int testLl(){
	printf("\n\nTesting thread_create() after the scheduler has been activated by thread_join()\n" );
	printf("thread 1, 2, 3 should finish before 4, 5, 6 \n\n\n" );


	thread_libinit(FIFO); // FIFO SJF PRIORITY

	//create
	int tid1 = thread_create(func, NULL, 0);
	int tid2 = thread_create(func, NULL, -1);
	int tid3 = thread_create(func, NULL, 1);


	// join
	thread_join(tid1);
	thread_join(tid2);
	thread_join(tid3);
	
	int tid4 = thread_create(func, NULL, 1);
	int tid5 = thread_create(func, NULL, 1);
	int tid6 = thread_create(func, NULL, 1);

	thread_join(tid4);
	thread_join(tid5);
	thread_join(tid6);



	// term
	thread_libterminate();

	return 1;
}


int main(){
  testLl();
  exit(EXIT_SUCCESS);
}
