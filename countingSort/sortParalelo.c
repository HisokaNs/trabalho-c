#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

#define SIZE 10
#define RANGE 235

void countingSort(int* array, int size) {
    int count[RANGE];
    memset(count, 0, sizeof(count));

    int* sortedArray = (int*)malloc(size * sizeof(int));

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        #pragma omp atomic
        count[array[i]]++;
    }

    int k = 0;
    for (int i = 0; i < RANGE; i++) {
        for (int j = 0; j < count[i]; j++) {
            sortedArray[k] = i;
            k++;
        }
    }
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        array[i] = sortedArray[i];
    }
    free(sortedArray);
}

int main() {
    int array[SIZE] = {6, 2, 9, 1, 45, 3, 88, 0, 78, 234};

    double start_time = omp_get_wtime();
    countingSort(array, SIZE);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Imprimir o array ordenado (opcional)
    printf("Array ordenado paralelo:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Tempo de execução: %f segundos\n", elapsed_time);
    return 0;
}
