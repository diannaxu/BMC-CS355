#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

int main(){
	printf("** This is a test for misuse. **\n");
	printf("** Should not crash or have memory leak **\n");
	printf("** Upon successful exit will print \"Exit success!!\"**\n");

	if (thread_yield() != -1) exit(EXIT_FAILURE);

	if (thread_libterminate() != -1) exit(EXIT_FAILURE);

	printf("Exit success!!\n");
	exit(EXIT_SUCCESS);
}