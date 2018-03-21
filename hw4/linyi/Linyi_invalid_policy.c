#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo(void *arg) {
}

/**
 * Simple FIFO test
 */
int main(void) {
  	printf("** Testing with invalide policy** \n");
  	printf("** Upon success will print \"Exit success!!\"**\n");
  	if (thread_libinit(10768760) == -1)
    	exit(EXIT_FAILURE);


  	if (thread_libterminate() == -1)
    	exit(EXIT_FAILURE);

	
	printf("Exit success!!\n");
  	exit(EXIT_SUCCESS);
}
