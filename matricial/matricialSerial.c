#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE_1 100000
#define SIZE_2 200000
#define SIZE_3 400000

int findMax_parallel(int* array, int size) {
    int max = array[0];

    #pragma omp parallel
    {
        int local_max = max;
        #pragma omp for
        for (int i = 1; i < size; i++) {
            if (array[i] > local_max) {
                local_max = array[i];
            }
        }
        #pragma omp reduction(max:max)
        {
            if (local_max > max) {
                max = local_max;
            }
        }
    }

    return max;
}
int findMax_serial(int* array, int size) {
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int main() {
    int array[SIZE_3];
    srand(12345);
    for (int i = 0; i < SIZE_3; i++) {
        array[i] = rand();
    }

    printf("Critério\t\tThreads\tSIZE_1\t\tSIZE_2\t\tSIZE_3\n");

    double start_time, end_time, elapsed_time_parallel;

    int max_parallel;
    for (int num_threads = 2; num_threads <= omp_get_max_threads(); num_threads *= 2) {
        printf("Tempo Paralelo\t%d\n", num_threads);
        for (int i = 0; i < 3; i++) {
            int size;
            if (i == 0)
                size = SIZE_1;
            else if (i == 1)
                size = SIZE_2;
            else
                size = SIZE_3;

            start_time = omp_get_wtime();
            max_parallel = findMax_parallel(array, size);
            end_time = omp_get_wtime();
            elapsed_time_parallel = end_time - start_time;

            double speedup = elapsed_time_serial_1 / elapsed_time_parallel;
            double efficiency = speedup / num_threads;

            printf("Tamanho: %d\t%.6f\t%.2f\t%.2f\n", size, elapsed_time_parallel, speedup, efficiency);
        }

        printf("\n");
    }

    return 0;
}
