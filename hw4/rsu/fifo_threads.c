#include "userthread.h"
// #include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef _REENTRANT
#define _REENTRANT
#endif

#define N 5
#define SUCCESS 1
#define FAIL -1

int A[N][N];
int B[N][N];
int C[N][N];
int MAX_ROW_SUM = 0;
//pthread_mutex_t mutex;

struct arg_struct {
  int i;
  int j;
};

int thread_wrapper(int threads[N][N], void (*start_routine) (void *));
void print_matrix(int *matrix, int m, int n);
void rowsum(void *arguments);
void multiply(void *arguments);
void write_num(void *arguments);

int main() {
  int threads[N][N];
  int threads2[N];

  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  thread_wrapper(threads, write_num);
  thread_wrapper(threads, multiply);

  printf("A:\n");
  print_matrix((int *)A, N, N);
  printf("B:\n");
  print_matrix((int *)B, N, N);
  printf("C:\n");
  print_matrix((int *)C, N, N);

  //pthread_mutex_init(&mutex,NULL);

  for (int i = 0; i < N; i++) {
    struct arg_struct *arg = malloc(sizeof(struct arg_struct));
    arg -> i = i;
    arg -> j = -1;
    if ((threads2[i] = thread_create(rowsum, (void *)arg, 0)) == FAIL){
      exit(EXIT_FAILURE);
    }
  }
  for (int i = 0; i < N; i++) {
    if (thread_join(threads2[i]) == FAIL){
      exit(EXIT_FAILURE);
    }
  }
  printf("Max row sum: %d\n",MAX_ROW_SUM);
  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}

int thread_wrapper(int threads[N][N], void (*start_routine) (void *)){
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      struct arg_struct *arg = malloc(sizeof(struct arg_struct));
      arg -> i = i;
      arg -> j = j;
      if ((threads[i][j] = thread_create(start_routine, (void *)arg, 0)) == FAIL){
        exit(EXIT_FAILURE);
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (thread_join(threads[i][j]) == FAIL){
        exit(EXIT_FAILURE);
      }
    }
  }
}

void print_matrix(int *matrix, int m, int n) {
  for (int i = 0 ;i < m; i++) {
    for (int j = 0 ;j < n; j++) {
      printf("%d ", *(matrix + i*n + j));
    }
    printf("\n");
  }
  printf("\n");
}

void rowsum(void *arguments){
  struct arg_struct *args = arguments;
  int i = args -> i;
  int row_sum = 0;
  for (int j = 0; j < N; j++) {
    row_sum += C[i][j];
  }
  //pthread_mutex_lock(&mutex);
  if ( MAX_ROW_SUM < row_sum) {
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    unsigned int seed1 = tv1.tv_sec * 1037 * tv1.tv_usec * 97;
    sleep(rand_r(&seed1) % 3 + 1);
    MAX_ROW_SUM = row_sum;
  }
  //pthread_mutex_unlock(&mutex);
  free(args);
}

void multiply(void *arguments) {
  struct arg_struct *args = arguments;
  int i = args->i;
  int j = args->j;
  C[i][j] = 0;
  for (int k = 0; k < N; k++) {
    C[i][j] += A[i][k] * B[k][j];
  }
  free(args);
}

void write_num(void *arguments) {
  struct timeval tv1;
  gettimeofday(&tv1, NULL);
  unsigned int seed1 = tv1.tv_sec * 1037 * tv1.tv_usec * 97;

  struct timeval tv2;
  gettimeofday(&tv2, NULL);
  unsigned int seed2 = tv2.tv_sec * 97 * tv2.tv_usec * 377;

  struct arg_struct *args = arguments;
  int i = args->i;
  int j = args->j;
  A[i][j] = rand_r(&seed1) % 9 + 1;
  B[i][j] = rand_r(&seed2) % 9 + 1;
  free(args);
}
