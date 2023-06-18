#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h> 

#define SIZE 5 

void matrixMultiplication(int** matrixA, int** matrixB, int** result, int size) { 
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
    int** matrixA = (int**)malloc(SIZE * sizeof(int*)); 
    int** matrixB = (int**)malloc(SIZE * sizeof(int*)); 
    int** result = (int**)malloc(SIZE * sizeof(int*)); 

    for (int i = 0; i < SIZE; i++) { 
        matrixA[i] = (int*)malloc(SIZE * sizeof(int)); 
        matrixB[i] = (int*)malloc(SIZE * sizeof(int)); 
        result[i] = (int*)malloc(SIZE * sizeof(int)); 
    } 

    // Preencher as matrizes com valores aleatórios 
    srand(12345); 
    for (int i = 0; i < SIZE; i++) { 
        for (int j = 0; j < SIZE; j++) { 
            matrixA[i][j] = rand(); 
            matrixB[i][j] = rand(); 
        } 
    } 

    double start_time = omp_get_wtime(); 
    matrixMultiplication(matrixA, matrixB, result, SIZE); 
    double end_time = omp_get_wtime(); 
    double elapsed_time = end_time - start_time; 

    // Imprimir a matriz resultante (opcional) 

    printf("Resultado:\n"); 
    for (int i = 0; i < SIZE; i++) { 
        for (int j = 0; j < SIZE; j++) { 
            printf("%d ", result[i][j]); 
        } 
        printf("\n"); 
    } 


    // Liberar memória 

    for (int i = 0; i < SIZE; i++) { 
        free(matrixA[i]); 
        free(matrixB[i]); 
        free(result[i]); 
    } 
    free(matrixA); 
    free(matrixB); 
    free(result); 

    return 0; 
} 