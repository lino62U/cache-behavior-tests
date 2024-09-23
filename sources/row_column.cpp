#include <iostream>
#include <fstream>
#include <ctime>
#include "row_column.h"

void initialize_matrices(double** A, double* x, double* y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = static_cast<double>(i + j);
        }
        x[i] = static_cast<double>(i);
        y[i] = 0.0;
    }
}

void loop_row_major(double** A, double* x, double* y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

void loop_column_major(double** A, double* x, double* y, int size) {
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

void writeResultsToCSV(const std::string& filename, int size, double rowMajorTime, double columnMajorTime) {
    std::ofstream file;
    file.open(filename, std::ios::app);
    if (file.is_open()) {
        file << size << "," << rowMajorTime << "," << columnMajorTime << "\n";
        file.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo CSV.\n";
    }
}