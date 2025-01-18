#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include <stdbool.h>
#include <stddef.h>

// Define a structure for our matrix

typedef struct {
  double *data; // Pointer to the matrix elements (row-major order)
  size_t rows;  // Number of rows
  size_t cols;  // Number of columns
} Matrix;

// Error Handling
typedef enum {
  MATRIX_SUCCESS,
  MATRIX_ERROR_NULL_POINTER,
  MATRIX_ERROR_INVALID_DIMENSIONS,
  MATRIX_ERROR_MEMORY_ALLOCATION,
  MATRIX_ERROR_INCOMPATIBLE_DIMENSIONS
} MatrixStatus;

// Function Prototypes:

// Create and destroy matrices
MatrixStatus matrix_create(size_t rows, size_t cols, Matrix *out);
void matrix_destroy(Matrix *matrix);

// Accessor functions
MatrixStatus matrix_get(const Matrix *matrix, size_t row, size_t col,
                        double *out);
MatrixStatus matrix_set(Matrix *matrix, size_t row, size_t col, double value);

// Basic matrix operations
MatrixStatus matrix_add(const Matrix *a, const Matrix *b, Matrix *out);
MatrixStatus matrix_subtract(const Matrix *a, const Matrix *b, Matrix *out);
MatrixStatus matrix_multiply(const Matrix *a, const Matrix *b, Matrix *out);
MatrixStatus matrix_transpose(const Matrix *in, Matrix *out);
MatrixStatus matrix_scalar_multiply(const Matrix *in, double scalar,
                                    Matrix *out);

// Utility functions
MatrixStatus matrix_print(const Matrix *matrix);
MatrixStatus matrix_fill(Matrix *matrix, double value);

// Additional advanced functions
MatrixStatus matrix_identity(size_t n,
                             Matrix *out); // Creates an Identity matrix

#endif
