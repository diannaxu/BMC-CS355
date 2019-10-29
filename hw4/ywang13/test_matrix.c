// Author: Yuxiao Wang
// test PRIORITY lib using matrix file in HW2

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "userthread.h"

#ifndef _REENTRANT
#define _REENTRANT
#endif

#define N 5
#define MATRIX_RAND_MAX 100

struct arg_struct {
    int** A;
    int** B;
};
struct timeval t;
pthread_mutex_t mutex_matrix[N][N];

void* writeint(void*);
int randint(int max);
void printmatrix(int** matrix, char* name);

int main(int argc, const char** argv) {
    // malloc matrices
    int** A = malloc(N * sizeof(*A));
    int** B = malloc(N * sizeof(*B));
    for (int i = 0; i < N; ++i) {
        A[i] = malloc(N * sizeof(**A));
        B[i] = malloc(N * sizeof(**B));
    }

    // init mutex
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            pthread_mutex_init(&mutex_matrix[i][j], NULL);
        }
    }

    thread_libinit(PRIORITY);

    // create threads with `writeint` job
    int threads[N * N];
    struct arg_struct arg = {A, B};
    for (int i = 0; i < N * N; ++i) {
        threads[i] = thread_create((void (*)(void *)) writeint, &arg, randint(3) - 2);
    }
    // wait for threads
    for (int i = 0; i < N * N; ++i) {
        thread_join(threads[i]);
    }

    // unlock mutex
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            pthread_mutex_unlock(&mutex_matrix[i][j]);
        }
    }

    printmatrix(A, "A");
    printmatrix(B, "B");

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            pthread_mutex_destroy(&mutex_matrix[i][j]);
        }
    }
    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
    }

    free(A);
    free(B);
    thread_libterminate();
    return 0;
}

void* writeint(void* arg) {
    struct arg_struct* matrices = (struct arg_struct*) arg;
    int** A = matrices->A;
    int** B = matrices->B;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // trylock
            if (pthread_mutex_trylock(&mutex_matrix[i][j]) == 0) {
                // write to entry
                A[i][j] = randint(MATRIX_RAND_MAX);
                // write into the same location in B
                usleep(1); // sleep to avoid same rand seed
                B[i][j] = randint(MATRIX_RAND_MAX);
                goto DONE;
            }
        }
    }

    DONE:
    return NULL;
}

// random integer between (0, max]
int randint(int max) {
    gettimeofday(&t, NULL);
    unsigned seed = t.tv_usec;
    return rand_r(&seed) % max + 1;
}

// dot product of the ith row in A and jth row in B
int dotproduct(int** A, int** B, int i, int j) {
    int sum = 0;
    for (int k = 0; k < N; ++k) {
        sum += A[i][k] * B[k][j];
    }
    return sum;
}

void printmatrix(int** matrix, char* name) {
    printf("\n************* printing matrix %s *************\n", name);
    for (int** ptri = matrix; ptri - matrix < N; ++ptri) {
        for (int* ptrj = *ptri; ptrj - *ptri < N; ++ptrj) {
            printf("%d\t", *ptrj);
        }
        printf("\n");
    }
}
