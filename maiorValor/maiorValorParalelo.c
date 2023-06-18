#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

int findMax_parallel(int* array, int size) {
    int max = array[0];
    #pragma omp parallel for reduction(max:max)
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int main() {
    int array[SIZE];

    // Preencher o vetor com valores aleatórios
    srand(12345);
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand();
    }

    double start_time = omp_get_wtime();

    int max = findMax_parallel(array, SIZE);

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    printf("Maior elemento encontrado: %d\n", max);
    printf("Tempo de execução: %f segundos\n", elapsed_time);

    return 0;
}