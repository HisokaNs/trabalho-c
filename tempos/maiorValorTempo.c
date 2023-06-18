#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE_1 400000
#define SIZE_2 600000
#define SIZE_3 800000

int findMax_serial(int* array, int size) {
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

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
        #pragma omp critical
        {
            if (local_max > max) {
                max = local_max;
            }
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

    printf("Critério\tThreads\tSIZE_1\t\tSIZE_2\t\tSIZE_3\n");

    double start_time = omp_get_wtime();
    int max_serial_1 = findMax_serial(array, SIZE_1);
    double end_time = omp_get_wtime();
    double elapsed_time_serial_1 = end_time - start_time;

    start_time = omp_get_wtime();
    int max_serial_2 = findMax_serial(array, SIZE_2);
    end_time = omp_get_wtime();
    double elapsed_time_serial_2 = end_time - start_time;

    start_time = omp_get_wtime();
    int max_serial_3 = findMax_serial(array, SIZE_3);
    end_time = omp_get_wtime();
    double elapsed_time_serial_3 = end_time - start_time;

    printf("Tempo Serial\t1\t%.6f\t%.6f\t%.6f\n", elapsed_time_serial_1, elapsed_time_serial_2, elapsed_time_serial_3);

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

            start_time = omp_get_wtime();
            int max_parallel = findMax_parallel(array, size);
            end_time = omp_get_wtime();
            double elapsed_time_parallel = end_time - start_time;

            printf("Tamanho: %d\t%.6f\n", size, elapsed_time_parallel);
        }
        printf("\n");
    }

    return 0;
}
