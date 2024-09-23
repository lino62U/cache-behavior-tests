#include <iostream>
#include <fstream>
#include <ctime>
#include "row_column.h"
using namespace std;


int main(int argc, char* argv[]) {
    string filename = "result/times_row_column.csv";
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <tamaño_matriz>\n";
        return 1;
    }

    int size = atoi(argv[1]);

    // Inicializar matrices dinámicamente
    double** A = new double*[size];
    for (int j = 0; j < size; j++) {
        A[j] = new double[size];
    }
    double* x = new double[size];
    double* y = new double[size];

    initialize_matrices(A, x, y, size);

    // Medir tiempo de multiplicación por filas (row-major)
    clock_t start = clock();
    loop_row_major(A, x, y, size);
    clock_t end = clock();
    double rowMajorTime = double(end - start) / CLOCKS_PER_SEC;
    cout << "-- Tiempo de ejecución del bucle row-major: " << rowMajorTime << " segundos\n";

    // Reiniciar vector y para el segundo bucle (column-major)
    for (int j = 0; j < size; j++) {
        y[j] = 0.0;
    }

    // Medir tiempo de multiplicación por columnas (column-major)
    start = clock();
    loop_column_major(A, x, y, size);
    end = clock();
    double columnMajorTime = double(end - start) / CLOCKS_PER_SEC;
    cout << "-- Tiempo de ejecución del bucle column-major: " << columnMajorTime << " segundos\n";

    // Guardar resultados en el archivo CSV
    writeResultsToCSV(filename, size, rowMajorTime, columnMajorTime);

    for (int j = 0; j < size; j++) {
        delete[] A[j];
    }
    delete[] A;
    delete[] x;
    delete[] y;

    return 0;
}
