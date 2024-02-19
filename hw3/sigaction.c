//Ben Jiang, Kai Britt and Victor Nault

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
pid_t pid;


void sighandler(int signal, siginfo_t *info, void *ucontext){
    if(info->si_code == CLD_EXITED){ //si_code in the info struct contains if the child is suspended, exited, or interrupted...
        printf("Child exited\n");
    }
    else if(info->si_code == CLD_KILLED){
        printf("Child killed\n");
    }
    else if(info->si_code == CLD_STOPPED){
        printf("Child stopped\n");
    }
}

int main(){
    struct sigaction my_sigaction; //declaring the struct that contains the pointer to sighandler with extra information and flag
    my_sigaction.sa_sigaction = sighandler; //setting the sighandler 
    my_sigaction.sa_flags = SA_SIGINFO; //setting the flag to say we want more information

    sigaction(SIGCHLD,&my_sigaction,NULL); //this is like signal(), setting a handler for SIGCHLD

    //below are tests
    int status;
    pid = fork();

    if(pid > 0){
        //kill(pid,SIGINT);
        kill(pid,SIGSTOP);
    }

    // if(pid == 0){
    //     exit(0);
    // }

    wait(&status);
}

