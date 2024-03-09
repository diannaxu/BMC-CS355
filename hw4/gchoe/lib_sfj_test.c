/**
 * Author: gchoe
 * Purpose: Simple test to ensure the library (libinit and libterminate)
 * works accordingly with SFJ.
 */

int main() {
    if (thread_libinit(SFJ) == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with SFJ initialized successfully.\n");

    if (thread_libterminate() == -1) {
        exit(EXIT_FAILURE);
    }

    printf("Thread library with SFJ terminated successfully.\n");

    exit(EXIT_SUCCESS);
}