/**
 * test 7 - fifo thread creates thread
 * 
 * Author: Cecilia Zhang
 * 
 * Description: Checks FIFO scheduling with creating 2 additional threads from 
 *              the "parent" thread that was launched in main. Main creates 1 parent 
 *              thread to run a func that creates 2 child threads. 
 * 
 * Expected output: 
 * 
 * test 7
 * Parent task: Creating 2 child threads...
 * Parent task: Waiting for child threads to join...
 * Child task 1: done!!
 * Child task 2: done!!
 * Parent task: Child threads finished
 * done
*/

#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>

void child_task(void *arg) {
    int id = *(int *)arg;
    printf("Child task %d: done!!\n", id);
}

void parent_task(void *arg) {
    int child_id1 = 1;
    int child_id2 = 2;

    printf("Parent task: Creating 2 child threads...\n");

    int child_tid1 = thread_create(child_task, &child_id1, 0);
    int child_tid2 = thread_create(child_task, &child_id2, 0);

    if (child_tid1 == -1 || child_tid2 == -1) {
        printf("Can't create child threads\n");
        exit(EXIT_FAILURE);
    }

    printf("Parent task: Waiting for child threads to join...\n");

    thread_yield();

    if (thread_join(child_tid1) == -1 || thread_join(child_tid2) == -1) {
        printf("Can't join child threads\n");
        exit(EXIT_FAILURE);
    }

    printf("Parent task: Child threads finished\n");
}

int main() {
    if (thread_libinit(FIFO) == -1) {
        printf("Can't init lib\n");
        exit(EXIT_FAILURE);
    };

    printf("test 7\n"); 

    int parent_tid = thread_create(parent_task, NULL, 0);

    if (parent_tid == -1) {
        printf("Can't create parent thread\n");
        exit(EXIT_FAILURE);
    }

    if (thread_join(parent_tid) == -1) {
        printf("Can't join parent thread\n");
        exit(EXIT_FAILURE);
    }

    printf("done\n");

    if (thread_libterminate() == -1) {
        printf("Can't terminate lib\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
