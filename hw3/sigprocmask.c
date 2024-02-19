/*********************************
* FILENAME :        sigprocmask.c
*
* DESCRIPTION : This file demonstrates how the sigproc family 
* work; specifically sigprocmask(), sigemptyset(), sigaddset()
* 
* A signal handler for SIGINT is registered. Then SIGINT is added 
* to signal_set using sigaddset() Then sigprocmask is used
* to block all the signals in signal_set aka SIGINT
* Once SIGINT is blocked Crtl+C won't work. 
* Though you can still kill the process though its pid
* 
* After 20 seconds, the program will wake up and unblock
* SIGINT using sigemptyset() Any signals which were pending 
* when SIGINT was blocked will be recieved by the handler. 
*
*AUTHOR : @aahmed1, @gchoe
**/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("Received signal: %d\n", signum);
}

int main() {
   

   // Define signal sets
   sigset_t signal_set;

   // Register signal handler for SIGINT
   if (signal(SIGINT, handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
   }

    // Add SIGINT to the set
   if(sigaddset(&signal_set, SIGINT) != 0){
		perror("sigaddset:");
		exit(EXIT_FAILURE);
	}

   // Block SIGINT signal
   if(sigprocmask(SIG_SETMASK, &signal_set, NULL) != 0){
		perror("sigprocmask:");
		exit(EXIT_FAILURE);
	}


   printf("\nSIGINT signal is now blocked.\n");
   printf("Try Ctrl+C. Try killing this program with 'kill -kill %d'", getpid());
   printf(".\nGoing to sleep for 20 seconds.\n\n");

   sleep(20);

   printf("\n\nI just woke up!.\n");
   printf("I will unblock SIGINT so the signals you sent can be triggered!.\n");
   printf("Now removing all signals from mask.\n\n");
	
   if(sigemptyset(&signal_set) != 0)
	{
		perror("sigemptyset:");
		exit(EXIT_FAILURE);
	}

    // Unblock SIGINT signal
   if(sigprocmask(SIG_SETMASK, &signal_set, NULL) != 0)
	{
		perror("sigprocmask:");
		exit(EXIT_FAILURE);
	}

   printf("SIGINT signal is unblocked.\n");

   return 0;
}
