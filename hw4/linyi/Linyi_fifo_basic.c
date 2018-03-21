#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo(void *arg){
	printf("%s", arg);
}

int main(){
	printf("** This is a basic fifo test. **\n");
	printf("** Will create and join three threads. **\n");
	printf("** Upon success will print \"Exit success!!\"**\n");

	char *arg = "";
	int tid1, tid2, tid3;
	if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);

	tid1 = thread_create(foo, arg, 1);
	if (tid1 == -1) exit(EXIT_FAILURE);

	tid2 = thread_create(foo, arg, 1);
	if (tid2 == -1) exit(EXIT_FAILURE);

	tid3 = thread_create(foo, arg, 1);
	if (tid3 == -1) exit(EXIT_FAILURE);

	if (thread_join(1) == -1) exit(EXIT_FAILURE);

	if (thread_join(2) == -1) exit(EXIT_FAILURE);

	if (thread_join(3) == -1) exit(EXIT_FAILURE);

	if (thread_libterminate() == -1) exit(EXIT_FAILURE);

	printf("Exit success!!\n");
	exit(EXIT_SUCCESS);
}