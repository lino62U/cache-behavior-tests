#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

// Función para multiplicar matrices clásicamente
void multiplyClassic(int* A, int* B, int* C, int n);

// Función para multiplicar matrices por bloques
void multiplyByBlocks(int* A, int* B, int* C, int n, int blockSize);

// Función para inicializar matrices
void initializeMatrix(int* matrix, int n);

#endif