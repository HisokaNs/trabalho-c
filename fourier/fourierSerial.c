#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <omp.h>

#define SIZE 10

void dft_serial(double complex* input, double complex* output, int size) {
    for (int k = 0; k < size; k++) {
        output[k] = 0;
        for (int n = 0; n < size; n++) {
            double complex exponent = -2.0 * M_PI * k * n / size;
            output[k] += input[n] * cexp(exponent);
        }
    }
}

int main() {
    double complex input[SIZE];
    double complex output[SIZE];

    srand(12345);
    for (int i = 0; i < SIZE; i++) {
        input[i] = rand() / (RAND_MAX + 1.0) + rand() / (double)RAND_MAX * I;
    }

    double start_time = omp_get_wtime();
    dft_serial(input, output, SIZE);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("Tempo de execução: %f segundos\n", elapsed_time); 

    printf("Vetor de saída:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("(%f, %f) ", creal(output[i]), cimag(output[i]));
    }
    printf("\n");


    return 0;
}
