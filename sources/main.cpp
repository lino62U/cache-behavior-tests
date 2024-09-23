#include <iostream>
#include <ctime>
#include "matrix_utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <tamaño_matriz>\n";
        return 1;
    }

    int size = atoi(argv[1]);
    const int blockSize = 64;

    // Inicializar matrices dinámicamente
    int* A = new int[size * size];
    int* B = new int[size * size];
    int* C1 = new int[size * size]();
    int* C2 = new int[size * size]();

    // Inicializar las matrices A y B con valores aleatorios
    initializeMatrix(A, size);
    initializeMatrix(B, size);

    // Medir tiempo de multiplicación clásica
    clock_t start = clock();
    multiplyClassic(A, B, C1, size);
    clock_t end = clock();
    double durationClassic = double(end - start) / CLOCKS_PER_SEC;
    cout << "-- Tiempo de multiplicación clásica: " << durationClassic << " segundos\n";

    // Medir tiempo de multiplicación por bloques
    start = clock();
    multiplyByBlocks(A, B, C2, size, blockSize);
    end = clock();
    double durationBlocks = double(end - start) / CLOCKS_PER_SEC;
    cout << "-- Tiempo de multiplicación por bloques: " << durationBlocks << " segundos\n";

    // Liberar la memoria
    delete[] A;
    delete[] B;
    delete[] C1;
    delete[] C2;

    return 0;
}
