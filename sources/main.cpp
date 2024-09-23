#include <iostream>
#include <fstream>  // Para trabajar con archivos
#include <ctime>
#include "matrix_utils.h"

using namespace std;

// Función para agregar resultados en un archivo CSV
void appendResultsToCSV(const string& filename, int size, double durationClassic, double durationBlocks) {
    ofstream file;
    // Abrir el archivo en modo "append" para agregar sin sobrescribir
    file.open(filename, ios::app);
    if (file.is_open()) {
        // Agregar tamaño y tiempos en el archivo CSV
        file << size << "," << durationClassic << "," << durationBlocks << "\n";
        file.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo CSV.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <tamaño_matriz> [--save]\n";
        return 1;
    }

    int size = atoi(argv[1]);
    bool saveResults = false;

    // Verificar si el argumento "--save" fue proporcionado
    if (argc >= 3 && string(argv[2]) == "--save") {
        saveResults = true;
    }

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

    // Medir tiempo de multiplicación por bloques
    start = clock();
    multiplyByBlocks(A, B, C2, size, blockSize);
    end = clock();
    double durationBlocks = double(end - start) / CLOCKS_PER_SEC;

    // Si se proporciona la opción --save, imprimir y guardar los resultados
    if (saveResults) {
        cout << "-- Tiempo de multiplicación clásica: " << durationClassic << " segundos\n";
        cout << "-- Tiempo de multiplicación por bloques: " << durationBlocks << " segundos\n";
        appendResultsToCSV("result/times_block_classic.csv", size, durationClassic, durationBlocks);
    }

    // Liberar la memoria
    delete[] A;
    delete[] B;
    delete[] C1;
    delete[] C2;

    return 0;
}
