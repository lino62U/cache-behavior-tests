#include <iostream>
#include <ctime>

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

int main() {
    const int sizes[] = {100, 1000, 5000, 10000};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int k = 0; k < num_sizes; ++k) {
        int size = sizes[k];

        if (size > 10000) {
            std::cout << "Advertencia: Tamaño de matriz " << size << "x" << size << " es muy grande. Puede causar problemas de memoria.\n";
        }

        std::cout << "Probando tamaño de matriz: " << size << "x" << size << std::endl;

        double** A = new double*[size];
        for (int i = 0; i < size; i++) {
            A[i] = new double[size];
        }
        double* x = new double[size];
        double* y = new double[size];

        initialize_matrices(A, x, y, size);

        // Medir el tiempo del primer bucle (row-major)
        clock_t start = clock();
        loop_row_major(A, x, y, size);
        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC;
        std::cout << "Tiempo de ejecución del primer bucle (row-major) con tamaño " << size << ": " << duration << " segundos.\n";

        // Reiniciar vector y para el segundo bucle
        for (int i = 0; i < size; i++) {
            y[i] = 0.0;
        }

        // Medir el tiempo del segundo bucle (column-major)
        start = clock();
        loop_column_major(A, x, y, size);
        end = clock();
        duration = double(end - start) / CLOCKS_PER_SEC;
        std::cout << "Tiempo de ejecución del segundo bucle (column-major) con tamaño " << size << ": " << duration << " segundos.\n";

        for (int i = 0; i < size; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] x;
        delete[] y;

        std::cout << std::endl;
    }

    return 0;
}
