#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <omp.h>

#define SIZE_1 1000
#define SIZE_2 3000
#define SIZE_3 5000

void dft_serial(double complex* input, double complex* output, int size) {
    for (int k = 0; k < size; k++) {
        output[k] = 0;
        for (int n = 0; n < size; n++) {
            double complex exponent = -2.0 * M_PI * k * n / size;
            output[k] += input[n] * cexp(exponent);
        }
    }
}

void dft_parallel(double complex* input, double complex* output, int size) {
    #pragma omp parallel for
    for (int k = 0; k < size; k++) {
        output[k] = 0;
        for (int n = 0; n < size; n++) {
            double complex exponent = -2.0 * M_PI * k * n / size;
            output[k] += input[n] * cexp(exponent);
        }
    }
}

int main() {
    double complex input_1[SIZE_1];
    double complex output_1[SIZE_1];
    double complex input_2[SIZE_2];
    double complex output_2[SIZE_2];
    double complex input_3[SIZE_3];
    double complex output_3[SIZE_3];

    // Preencher os vetores de entrada com valores aleatórios
    srand(12345);
    for (int i = 0; i < SIZE_1; i++) {
        input_1[i] = rand() / (RAND_MAX + 1.0) + rand() / (double)RAND_MAX * I;
    }
    for (int i = 0; i < SIZE_2; i++) {
        input_2[i] = rand() / (RAND_MAX + 1.0) + rand() / (double)RAND_MAX * I;
    }
    for (int i = 0; i < SIZE_3; i++) {
        input_3[i] = rand() / (RAND_MAX + 1.0) + rand() / (double)RAND_MAX * I;
    }

    printf("Critério\t\tThreads\tSIZE_1\t\tSIZE_2\t\tSIZE_3\n");

    double elapsed_time_serial;

    // DFT Serial
    elapsed_time_serial = omp_get_wtime();
    dft_serial(input_1, output_1, SIZE_1);
    elapsed_time_serial = omp_get_wtime() - elapsed_time_serial;

    printf("Tempo Serial\t1\t%.6f\t", elapsed_time_serial);

    elapsed_time_serial = omp_get_wtime();
    dft_serial(input_2, output_2, SIZE_2);
    elapsed_time_serial = omp_get_wtime() - elapsed_time_serial;

    printf("%.6f\t", elapsed_time_serial);

    elapsed_time_serial = omp_get_wtime();
    dft_serial(input_3, output_3, SIZE_3);
    elapsed_time_serial = omp_get_wtime() - elapsed_time_serial;

    printf("%.6f\n", elapsed_time_serial);

    // DFT Paralelo
    printf("Tempo Paralelo");

    for (int num_threads = 1; num_threads <= 4; num_threads *= 2) {
        omp_set_num_threads(num_threads);

        double elapsed_time_parallel;

        elapsed_time_parallel = omp_get_wtime();
        dft_parallel(input_1, output_1, SIZE_1);
        elapsed_time_parallel = omp_get_wtime() - elapsed_time_parallel;

        printf("\t%d\t%.6f\t", num_threads, elapsed_time_parallel);

        elapsed_time_parallel = omp_get_wtime();
        dft_parallel(input_2, output_2, SIZE_2);
        elapsed_time_parallel = omp_get_wtime() - elapsed_time_parallel;

        printf("%.6f\t", elapsed_time_parallel);

        elapsed_time_parallel = omp_get_wtime();
        dft_parallel(input_3, output_3, SIZE_3);
        elapsed_time_parallel = omp_get_wtime() - elapsed_time_parallel;

        printf("%.6f\n", elapsed_time_parallel);
    }

    return 0;
}
