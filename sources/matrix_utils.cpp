#include "matrix_utils.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

void multiplyClassic(int* A, int* B, int* C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void multiplyByBlocks(int* A, int* B, int* C, int n, int blockSize) {
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                for (int ii = i; ii < min(i + blockSize, n); ii++) {
                    for (int jj = j; jj < min(j + blockSize, n); jj++) {
                        int sum = 0;
                        for (int kk = k; kk < min(k + blockSize, n); kk++) {
                            sum += A[ii * n + kk] * B[kk * n + jj];
                        }
                        C[ii * n + jj] += sum;
                    }
                }
            }
        }
    }
}

void initializeMatrix(int* matrix, int n) {
    for (int i = 0; i < n * n; i++) {
        matrix[i] = rand() % 10;
    }
}