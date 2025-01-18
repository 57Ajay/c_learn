#include "matrixLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Helper Function ---
static bool validate_bounds(const Matrix* matrix, size_t row, size_t col) {
    return matrix && row < matrix->rows && col < matrix->cols;
}

// --- Matrix Creation and Destruction ---
MatrixStatus matrix_create(size_t rows, size_t cols, Matrix* out) {
    if (!out) {
        return MATRIX_ERROR_NULL_POINTER;
    }

    if (rows == 0 || cols == 0) {
        return MATRIX_ERROR_INVALID_DIMENSIONS;
    }

    out->data = (double*)malloc(rows * cols * sizeof(double));
    if (!out->data) {
        return MATRIX_ERROR_MEMORY_ALLOCATION;
    }

    out->rows = rows;
    out->cols = cols;
    return MATRIX_SUCCESS;
}

void matrix_destroy(Matrix* matrix) {
    if (matrix) {
        free(matrix->data);
        matrix->data = NULL;
        matrix->rows = 0;
        matrix->cols = 0;
    }
}


// --- Accessor Functions ---
MatrixStatus matrix_get(const Matrix* matrix, size_t row, size_t col, double* out) {
    if (!matrix || !out) {
        return MATRIX_ERROR_NULL_POINTER;
    }

    if (!validate_bounds(matrix, row, col)) {
        return MATRIX_ERROR_INVALID_DIMENSIONS;
    }

    *out = matrix->data[row * matrix->cols + col];
    return MATRIX_SUCCESS;
}


MatrixStatus matrix_set(Matrix* matrix, size_t row, size_t col, double value) {
    if (!matrix) {
        return MATRIX_ERROR_NULL_POINTER;
    }

    if (!validate_bounds(matrix, row, col)) {
        return MATRIX_ERROR_INVALID_DIMENSIONS;
    }

    matrix->data[row * matrix->cols + col] = value;
    return MATRIX_SUCCESS;
}

// --- Basic Matrix Operations ---
MatrixStatus matrix_add(const Matrix* a, const Matrix* b, Matrix* out) {
    if (!a || !b || !out) return MATRIX_ERROR_NULL_POINTER;
    if (a->rows != b->rows || a->cols != b->cols) return MATRIX_ERROR_INCOMPATIBLE_DIMENSIONS;
    if (matrix_create(a->rows, a->cols, out) != MATRIX_SUCCESS) return MATRIX_ERROR_MEMORY_ALLOCATION;

    size_t size = a->rows * a->cols;
    for (size_t i = 0; i < size; i++) {
      out->data[i] = a->data[i] + b->data[i];
    }
    return MATRIX_SUCCESS;
}

MatrixStatus matrix_subtract(const Matrix* a, const Matrix* b, Matrix* out) {
    if (!a || !b || !out) return MATRIX_ERROR_NULL_POINTER;
    if (a->rows != b->rows || a->cols != b->cols) return MATRIX_ERROR_INCOMPATIBLE_DIMENSIONS;
    if (matrix_create(a->rows, a->cols, out) != MATRIX_SUCCESS) return MATRIX_ERROR_MEMORY_ALLOCATION;

    size_t size = a->rows * a->cols;
    for (size_t i = 0; i < size; i++) {
      out->data[i] = a->data[i] - b->data[i];
    }
    return MATRIX_SUCCESS;
}

MatrixStatus matrix_multiply(const Matrix* a, const Matrix* b, Matrix* out) {
    if (!a || !b || !out) return MATRIX_ERROR_NULL_POINTER;
    if (a->cols != b->rows) return MATRIX_ERROR_INCOMPATIBLE_DIMENSIONS;

    if (matrix_create(a->rows, b->cols, out) != MATRIX_SUCCESS) return MATRIX_ERROR_MEMORY_ALLOCATION;

    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            double sum = 0;
            for (size_t k = 0; k < a->cols; k++) {
                sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            out->data[i * out->cols + j] = sum;
        }
    }
    return MATRIX_SUCCESS;
}


MatrixStatus matrix_transpose(const Matrix* in, Matrix* out){
     if (!in || !out) return MATRIX_ERROR_NULL_POINTER;

    if (matrix_create(in->cols, in->rows, out) != MATRIX_SUCCESS) return MATRIX_ERROR_MEMORY_ALLOCATION;

    for(size_t i = 0; i < in->rows; i++){
        for(size_t j = 0; j < in->cols; j++){
            out->data[j * out->cols + i] = in->data[i * in->cols + j];
        }
    }
    return MATRIX_SUCCESS;
}

MatrixStatus matrix_scalar_multiply(const Matrix* in, double scalar, Matrix* out) {
   if (!in || !out) return MATRIX_ERROR_NULL_POINTER;
    if (matrix_create(in->rows, in->cols, out) != MATRIX_SUCCESS) return MATRIX_ERROR_MEMORY_ALLOCATION;

    size_t size = in->rows * in->cols;
    for (size_t i = 0; i < size; i++) {
      out->data[i] = in->data[i] * scalar;
    }
    return MATRIX_SUCCESS;

}

// --- Utility Functions ---
MatrixStatus matrix_print(const Matrix* matrix) {
    if (!matrix) {
      return MATRIX_ERROR_NULL_POINTER;
    }
    
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            printf("%lf ", matrix->data[i * matrix->cols + j]);
        }
        printf("\n");
    }
    return MATRIX_SUCCESS;
}

MatrixStatus matrix_fill(Matrix *matrix, double value){
    if(!matrix){
        return MATRIX_ERROR_NULL_POINTER;
    }

    size_t size = matrix->rows * matrix->cols;
    for(size_t i = 0; i < size; i++){
        matrix->data[i] = value;
    }
    return MATRIX_SUCCESS;
}


// --- Additional Advanced Function ---
MatrixStatus matrix_identity(size_t n, Matrix* out){
    if(!out) return MATRIX_ERROR_NULL_POINTER;
    if(n == 0) return MATRIX_ERROR_INVALID_DIMENSIONS;

    if(matrix_create(n, n, out) != MATRIX_SUCCESS) return MATRIX_ERROR_MEMORY_ALLOCATION;
    if (matrix_fill(out, 0.0) != MATRIX_SUCCESS) {
        matrix_destroy(out);
        return MATRIX_ERROR_MEMORY_ALLOCATION; //Or another failure reason
    }

     for(size_t i = 0; i < n; i++){
         out->data[i*n+i] = 1.0;
     }
    
    return MATRIX_SUCCESS;
}
