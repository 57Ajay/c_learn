#include <stdio.h>
#include <stdlib.h>

int mainMatrixBetter() {
    int rows, cols;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Allocate a single block of memory
    int *matrix = (int *)malloc(rows * cols * sizeof(int));
    if (matrix == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Accessing elements (using pointer arithmetic):
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = i * cols + j + 1; // Example initialization
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }

    free(matrix);
    matrix = NULL;

    return 0;
}

int mainMatrix() {
    int rows, cols;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Allocate memory for the rows (an array of int pointers)
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Allocate memory for each row (an array of ints)
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            perror("Memory allocation failed");
            // Free previously allocated memory in case of failure
            for(int j=0; j<i; j++){
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    // Initialize and access elements:
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1; // Example initialization
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Freeing the memory (VERY IMPORTANT!)
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;

    return 0;
}
