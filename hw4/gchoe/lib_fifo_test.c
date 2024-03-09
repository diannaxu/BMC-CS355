/**
 * Author: gchoe
 * Purpose: Simple test to ensure the library (libinit and libterminate)
 * works accordingly with FIFO.
 */

int main() {
    if (thread_libinit(FIFO) == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with FIFO initialized successfully.\n");

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with FIFO terminated successfully.\n");

    exit(EXIT_SUCCESS);
}