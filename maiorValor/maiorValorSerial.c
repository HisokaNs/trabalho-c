#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h> 

#define SIZE 1000000 

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

    int array[SIZE]; 
    // Preencher o vetor com valores aleatórios 
    srand(12345); 

    for (int i = 0; i < SIZE; i++) { 
        array[i] = rand(); 
    } 
    int max = findMax_serial(array, SIZE); 
    printf("Maior elemento encontrado: %d\n", max); 

    return 0; 
} 