//Juno Bartsch and Yang Wu
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//file to test sigaction
//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
//signum: any signal like SIGINT, SIGUSR, etc. Except SIGKILL and SIGSTOP
//act: new action for signal, can be NULL
//oldact: store previous action for signal, can be NULL
/*
struct sigaction {
    void     (*sa_handler)(int); //pointer to signal handling fn
    void     (*sa_sigaction)(int, siginfo_t *, void *); //pointer to signal catching fn
    sigset_t   sa_mask; //signals to add to signal mask
    int        sa_flags; //flags to modify behavior of a signal
    void     (*sa_restorer)(void); //ignore
};
*/
//siginfo_t: structure to store signal information
//SIGCHLD: sent to parent when child process terminates

//test sigaction
void sigchld_handler(int sig, siginfo_t *info, void *context) {
  if (info->si_code == CLD_EXITED) {
    printf("Child process %d exited with status %d\n", info->si_pid, info->si_status);
  } 
  else if (info->si_code == CLD_KILLED || info->si_code == CLD_DUMPED) {
    printf("Child process %d terminated by signal %d\n", info->si_pid, info->si_status);
  }
}

int main() {
    struct sigaction sa;

    // Set up the signal handler
    sa.sa_sigaction = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {  // Child process
        printf("Child process started with PID: %d\n", getpid());
        // Sleep
        sleep(2);
        // Exit
        exit(0);
    } else {  // Parent process
        printf("Parent process waiting for child to exit...\n");
        // Wait for the child to exit
        while (wait(NULL) != pid);
        printf("Parent process exiting.\n");
    }

    return 0;
}
