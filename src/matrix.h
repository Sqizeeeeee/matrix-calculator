#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

typedef struct {
    double** data; // pointer to data
    int rows; // property 1
    int cols; // property 2
} Matrix; // struct name

Matrix create_matrix(int rows, int cols);

void free_matrix(Matrix m);

Matrix matrix_add(Matrix a, Matrix b);
Matrix matrix_multiply(Matrix a, Matrix b);
Matrix matrix_transpose(Matrix m);

void print_matrix(Matrix m);
Matrix matrix_from_array(double* data, int rows, int cols);


bool matrix_is_symmetric(Matrix m, double tolerance);

#endif


// #ifndef  .... #endif : if not defined - define structure. Avoiding errors while compiling.