// Author: Paprika Chen
// Test if tasks with higher priority ends faster
// Right behavior: higher tasks ends faster shown in the output 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include "userthread.h"

void task(void* args) {
    int* info = (int*)args;
    int priority = info[0];
    int taskNum = info[1];
    
    printf("Task %d with priority %d started.\n", taskNum, priority);
    // Simulating work
    for (int i = 0; i < 3; i++) {
        sleep(1); // Simulate doing work
    }
    printf("Task %d with priority %d finished.\n", taskNum, priority);
}

int main(void) {
    if (thread_libinit(PRIORITY) == -1) {
        exit(EXIT_FAILURE);
    }

    int tasksInfo[][2] = {
        {-1, 1}, // Highest priority task
        {0, 2},  // Medium priority task
        {1, 3},  // Lowest priority task
        {-1, 4}, // Another highest priority task
        {0, 5},  // Another medium priority task
        {1, 6}   // Another lowest priority task
    };

    int numTasks = sizeof(tasksInfo) / sizeof(tasksInfo[0]);
    int tids[numTasks];

    for (int i = 0; i < numTasks; i++) {
        tids[i] = thread_create(task, &tasksInfo[i], tasksInfo[i][0]);
        if (tids[i] == -1) {
            printf("Failed to create task %d with priority %d\n", tasksInfo[i][1], tasksInfo[i][0]);
            thread_libterminate();
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numTasks; i++) {
        if (thread_join(tids[i]) == -1) {
            thread_libterminate();
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == -1) {
        printf("Failed to terminate thread library\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
