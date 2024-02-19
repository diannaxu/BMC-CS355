//Cecilia Zhang, Cecilia Chen, Paprika Chen

/* tcgetpgrp()/tcsetpgrp() - get and set terminal foreground process group
 * 
 * tcgetpgrp() returns the process group ID of the foreground process group on the terminal associated to fd. 
 * return the foreground process group ID of that terminal if there is one, and some value larger than 1 that is not 
 * presently a process group ID otherwise.
 * 
 * tcsetpgrp() makes the process group with process group ID pgrp the foreground process group on the terminal associated to fd.
 * When successful, tcsetpgrp() returns 0.  Otherwise, it returns -1, and errno is set appropriately.
 *
*/

/*
 * Description: This program demonstrates the use of tcsetpgrp() in a parent-child process scenario.
 * 
 * The program creates a child process and changes the terminal's foreground process group to the child process.
 * The child process prints its information and then exits. After that, the parent process restores the terminal's
 * foreground process group to the original one and exits. To run the program, use the following steps:
 * 
 * Compile:
 *   gcc tcsetpgrp.c -o tcsetpgrp
 * 
 * Run:
 *   ./tcsetpgrp
 * 
 * !!! NOTE: After running the program, the child process might be stopped, and a message 
 *          like '[1]+ Stopped ./demo' could be shown. To bring the stopped process back 
 *          to the foreground, use the 'fg' command in the terminal where the program was started.
 *          Also feel free to use ps to see current processes before and after entering 'fg'.
 *          If needed, use: 
 *          pkill -9 -f "tcsetpgrp" 
 *          to kill all processes if they don't exit temselves. 
"
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <termios.h>

int main() {
  printf("==========================\n");
  printf("Please read program description before running! \n");
  printf("This program is expected to stop in the middle, and you will need to enter 'fg' to terminal! \n");
  printf("Remember to use 'ps' command before and after entering 'fg'!\n");
  printf("==========================\n");

  pid_t child_pid;

  // Create a child process
  if ((child_pid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (child_pid == 0) {
    // child process
    printf("Child process with PID: %d, GID: %d\n", getpid(), getpgrp());

    // simulate some work
    sleep(2);

    printf("Child process exiting\n");
    exit(EXIT_SUCCESS);
  } else {
    // parent process
    printf("Parent process with PID: %d, GID: %d\n", getpid(), getpgrp());

    // save the current process group
    pid_t original_pgrp = getpgrp();

    // change the terminal's foreground process group to the child process
    if (tcsetpgrp(STDIN_FILENO, child_pid) == -1) {
      perror("tcsetpgrp");
      exit(EXIT_FAILURE);
    }

    printf("Parent process: Changed terminal foreground process group to child process\n");

    // wait for the child process to finish
    waitpid(child_pid, NULL, 0);

    // restore the original process group
    if (tcsetpgrp(STDIN_FILENO, original_pgrp) == -1) {
      perror("tcsetpgrp");
      exit(EXIT_FAILURE);
    }

    printf("Parent process: Restored terminal foreground process group to original\n");
    printf("Parent process exiting\n");
  }

  return 0;
}

