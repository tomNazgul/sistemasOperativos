#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define  N 2

int matrix1[N][N];
int matrix2[N][N];
int result[N][N];

void sum(void* arg);
void multiply(void* arg);
void init_matrix(int m[N][N]);
void print_matrix(int m[N][N]);

int main(int argc, char const *argv[]) {
  pthread_t thread[N];
  int rows[N];
  init_matrix(matrix1);
  init_matrix(matrix2);
  print_matrix(matrix1);
  print_matrix(matrix2);

  printf("N = %d", N);	

  for (int i = 0; i < N; i++) {
    rows[i] = i;
    pthread_create(&thread[i], NULL, (void*) &sum, (void*) &rows[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("%s\n", "Sum result:");
  print_matrix(result);

  for (int i = 0; i < N; i++) {
    rows[i] = i;
    pthread_create(&thread[i], NULL, (void*) &multiply, (void*) &rows[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("%s\n", "Multiply result:");
  print_matrix(result);

  return 0;
}

void init_matrix(int m[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      m[i][j] = rand() % 100;
    }
  }
}

void sum(void* arg) {
  int* intArgs = (int*) arg;
  int row = * intArgs;
  for (int j = 0; j < N; j++) {
    result[row][j] = matrix1[row][j] + matrix2[row][j];
  }
  pthread_exit(NULL);
}

void multiply(void* arg) {
  int* intArgs = (int*) arg;
  int row = * intArgs;
  for (int col = 0; col < N; col++) {
        result[row][col] = 0;
    for (int j = 0; j < N; j++) {
        result[row][col] += matrix1[row][j] * matrix2[j][row];
      }
  }
  pthread_exit(NULL);
}

void print_matrix(int m[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
