/**
 * Author: gchoe
 * Purpose: Simple test to ensure the library (libinit and libterminate)
 * works accordingly with PRIORITY.
 */

int main() {
    if (thread_libinit(PRIORITY) == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with PRIORITY initialized successfully.\n");

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with PRIORITY terminated successfully.\n");

    exit(EXIT_SUCCESS);
}