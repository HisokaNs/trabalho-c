#include <stdio.h> 

#include <stdlib.h> 

#include <omp.h> 

  

#define SIZE 10 

#define RANGE 1000000 

  

void countingSort(int* array, int size) { 

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

  

int main() { 

    int array[SIZE]; 

  

    // Preencher o array com valores aleatórios 

    srand(12345); 

    for (int i = 0; i < SIZE; i++) { 

        array[i] = rand() % RANGE; 

    } 

  

    double start_time = omp_get_wtime(); 

  

    countingSort(array, SIZE); 

  

    double end_time = omp_get_wtime(); 

    double elapsed_time = end_time - start_time; 

  

    // Imprimir o array ordenado (opcional)
    
    printf("Array ordenado:\n"); 

    for (int i = 0; i < SIZE; i++) { 

        printf("%d ", array[i]); 

    } 
    printf("\n"); 

    return 0; 

} 