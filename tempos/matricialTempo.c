#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE_1 100
#define SIZE_2 200
#define SIZE_3 400

void matrixMultiplicationSerial(int** matrixA, int** matrixB, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void matrixMultiplicationParalela(int** matrixA, int** matrixB, int** result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

int main() {
    int** matrixA = (int**)malloc(SIZE_3 * sizeof(int*));
    int** matrixB = (int**)malloc(SIZE_3 * sizeof(int*));
    int** result = (int**)malloc(SIZE_3 * sizeof(int*));

    for (int i = 0; i < SIZE_3; i++) {
        matrixA[i] = (int*)malloc(SIZE_3 * sizeof(int));
        matrixB[i] = (int*)malloc(SIZE_3 * sizeof(int));
        result[i] = (int*)malloc(SIZE_3 * sizeof(int));
    }

    // Preencher as matrizes com valores aleatórios
    srand(12);
    for (int i = 0; i < SIZE_3; i++) {
        for (int j = 0; j < SIZE_3; j++) {
            matrixA[i][j] = rand();
            matrixB[i][j] = rand();
        }
    }

    printf("Critério\t\tThreads\tSIZE_1\t\tSIZE_2\t\tSIZE_3\n");

    double start_time_serial = omp_get_wtime();
    matrixMultiplicationSerial(matrixA, matrixB, result, SIZE_3);
    double end_time_serial = omp_get_wtime();
    double elapsed_time_serial = end_time_serial - start_time_serial;

    printf("Tempo Serial\t1\t%.6f\t%.6f\t%.6f\n", elapsed_time_serial, elapsed_time_serial, elapsed_time_serial);

    for (int num_threads = 2; num_threads <= 4; num_threads *= 2) {
        printf("Tempo Paralelo\t%d\n", num_threads);
        for (int i = 0; i < 3; i++) {
            int size;
            if (i == 0)
                size = SIZE_1;
            else if (i == 1)
                size = SIZE_2;
            else
                size = SIZE_3;

            double start_time_parallel = omp_get_wtime();
            matrixMultiplicationParalela(matrixA, matrixB, result, size);
            double end_time_parallel = omp_get_wtime();
            double elapsed_time_parallel = end_time_parallel - start_time_parallel;

            printf("Tamanho: %d\t%.6f\n", size, elapsed_time_parallel);
        }
        printf("\n");
    }

    // Liberar memória
    for (int i = 0; i < SIZE_3; i++) {
        free(matrixA[i]);
        free(matrixB[i]);
        free(result[i]);
    }
    free(matrixA);
    free(matrixB);
    free(result);

    return 0;
}
