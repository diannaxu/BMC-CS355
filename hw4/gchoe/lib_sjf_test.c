/**
 * lib_sjf_test.c
 * Author: gchoe
 * Date: 3/8/2024
 * 
 * Description:
 * Simple test to ensure the library (libinit and libterminate)
 * works accordingly with SJF.
 *
 * Expected Result:
 * Success: Initialized thread library (SJF) successfully.
 * Success: Terminated thread library successfully.
 */

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

int main() {
    if (thread_libinit(SJF) == -1) {
        printf("ERROR: Failed to initialize thread library (SJF).\n");
        exit(EXIT_FAILURE);
    }

    printf("Success: Initialized thread library (SJF) successfully.\n");

    if (thread_libterminate() == -1) {
        printf("ERROR: Failed to terminate thread library.\n");
        exit(EXIT_FAILURE);
    }

    printf("Success: Terminated thread library successfully.\n");
    exit(EXIT_SUCCESS);
}