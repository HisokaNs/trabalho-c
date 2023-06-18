#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

#define SIZE_1 100
#define SIZE_2 1000
#define SIZE_3 10000
#define RANGE 1000000

void countingSortSerial(int* array, int size) {
    int count[RANGE] = {0};
    int* sortedArray = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    int k = 0;
    for (int i = 0; i < RANGE; i++) {
        for (int j = 0; j < count[i]; j++) {
            sortedArray[k] = i;
            k++;
        }
    }

    for (int i = 0; i < size; i++) {
        array[i] = sortedArray[i];
    }

    free(sortedArray);
}

void countingSortParallel(int* array, int size) {
    int count[RANGE] = {0};
    int* sortedArray = (int*)malloc(size * sizeof(int));

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        #pragma omp atomic
        count[array[i]]++;
    }

    int k = 0;
    #pragma omp parallel for
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
    int array_1[SIZE_1];
    int array_2[SIZE_2];
    int array_3[SIZE_3];

    // Preencher os arrays com valores aleatórios
    srand(12345);
    for (int i = 0; i < SIZE_1; i++) {
        array_1[i] = rand() % RANGE;
    }
    for (int i = 0; i < SIZE_2; i++) {
        array_2[i] = rand() % RANGE;
    }
    for (int i = 0; i < SIZE_3; i++) {
        array_3[i] = rand() % RANGE;
    }

    printf("Critério\t\tThreads\tSIZE_1\t\tSIZE_2\t\tSIZE_3\n");

    double elapsed_time_serial;

    // Counting Sort Serial
    elapsed_time_serial = omp_get_wtime();
    countingSortSerial(array_1, SIZE_1);
    elapsed_time_serial = omp_get_wtime() - elapsed_time_serial;

    printf("Tempo Serial\t1\t%.6f\t", elapsed_time_serial);

    elapsed_time_serial = omp_get_wtime();
    countingSortSerial(array_2, SIZE_2);
    elapsed_time_serial = omp_get_wtime() - elapsed_time_serial;

    printf("%.6f\t", elapsed_time_serial);

    elapsed_time_serial = omp_get_wtime();
    countingSortSerial(array_3, SIZE_3);
    elapsed_time_serial = omp_get_wtime() - elapsed_time_serial;

    printf("%.6f\n", elapsed_time_serial);

    // Counting Sort Paralelo
    printf("Tempo Paralelo");

    for (int num_threads = 1; num_threads <= 4; num_threads *= 2) {
        double elapsed_time_parallel;

        omp_set_num_threads(num_threads);

        elapsed_time_parallel = omp_get_wtime();
        countingSortParallel(array_1, SIZE_1);
        elapsed_time_parallel = omp_get_wtime() - elapsed_time_parallel;

        printf("\t%d\t%.6f\t", num_threads, elapsed_time_parallel);

        elapsed_time_parallel = omp_get_wtime();
        countingSortParallel(array_2, SIZE_2);
        elapsed_time_parallel = omp_get_wtime() - elapsed_time_parallel;

        printf("%.6f\t", elapsed_time_parallel);

        elapsed_time_parallel = omp_get_wtime();
        countingSortParallel(array_3, SIZE_3);
        elapsed_time_parallel = omp_get_wtime() - elapsed_time_parallel;

        printf("%.6f\n", elapsed_time_parallel);
    }

    return 0;
}
