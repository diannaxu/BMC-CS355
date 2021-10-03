#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


static void sigactionhandler(int sig, siginfo_t *si, void *unused){
	printf("status is: %d\n",si->si_code);
	kill(si->si_pid, SIGCONT);
	sleep(10);
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO; // | SA_NODEFER ;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sigactionhandler;
	if (sigaction(SIGCHLD, &sa, NULL) == -1){
		printf("failed to register sigaction handler");
              	exit(EXIT_FAILURE);
	}

	pid_t cpid, w;
	int wstatus;

	cpid = fork();
	if (cpid == -1) {
	perror("fork");
	exit(EXIT_FAILURE);
	}

	if (cpid == 0) {            /* Code executed by child */
	printf("Child PID is %ld\n", (long) getpid());
	do{}while(1);                    /* Wait for signals */

	} else {                    /* Code executed by parent */
	do {} while (1);
	exit(EXIT_SUCCESS);
	}
}


