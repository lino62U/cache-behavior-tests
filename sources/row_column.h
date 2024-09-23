#ifndef ROW_COLUMN_H
#define ROW_COLUMN_H

void initialize_matrices(double** A, double* x, double* y, int size);
void loop_row_major(double** A, double* x, double* y, int size);
void loop_column_major(double** A, double* x, double* y, int size);
void writeResultsToCSV(const std::string& filename, int size, double rowMajorTime, double columnMajorTime);

#endif // ROW_COLUMN_H