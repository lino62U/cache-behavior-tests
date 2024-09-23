#include <iostream>
#include <cstdlib>
#include <ctime> // Incluir para clock()

using namespace std;

// Función para multiplicar matrices clásicamente
void multiplyClassic(int* A, int* B, int* C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0; // C[i][j] es C[i * n + j]
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// Función para inicializar matrices con valores aleatorios
void initializeMatrix(int* matrix, int n) {
    for (int i = 0; i < n * n; i++) {
        matrix[i] = rand() % 10; // Valores aleatorios entre 0 y 9
    }
}

// Función para liberar la memoria de las matrices
void freeMatrix(int* matrix) {
    delete[] matrix;
}

int main() {
    // Tamaños de matrices a probar
    const int sizes[] = {2000}; // Tamaños de matrices a probar
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Realizar las pruebas para cada tamaño de matriz
    for (int k = 0; k < num_sizes; ++k) {
        int size = sizes[k];

        std::cout << "Probando tamaño de matriz: " << size << "x" << size << std::endl;

        // Inicializar matrices dinámicamente
        int* A = new int[size * size];
        int* B = new int[size * size];
        int* C1 = new int[size * size](); // Inicializa en 0

        // Inicializar las matrices A y B con valores aleatorios
        initializeMatrix(A, size);
        initializeMatrix(B, size);

        // Medir tiempo de multiplicación clásica
        clock_t start = clock();
        multiplyClassic(A, B, C1, size);
        clock_t end = clock();
        double durationClassic = double(end - start) / CLOCKS_PER_SEC; // Convertir a segundos
        cout << "Tiempo de multiplicación clásica: " << durationClassic << " segundos\n";

        // Liberar la memoria
        freeMatrix(A);
        freeMatrix(B);
        freeMatrix(C1);

        // Separador de pruebas
        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}
