#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "matrixLib.h"
/*
understanding pointers in-depth
with the help of structs
*/

typedef struct {
    char** names;
    int count;
}NameList;

int nameListMain(){
    NameList list;
    list.count = 3;
    list.names = (char**)malloc(list.count * sizeof(char*));
    if(list.names == NULL){
        perror("failed to allocate memory");
        return 1;
    }
    for(int i=0; i < list.count; i++){
        list.names[i] = (char*)malloc(50*sizeof(char));
        if(list.names[i] == NULL){
            perror("Allocation failed");
            return 1;
        }
    }
    strcpy(list.names[0], "AJay");
    strcpy(list.names[1], "Pranshu");
    strcpy(list.names[2], "Vasudev");
    for (int i=0;i<list.count; i++) {
         printf("Name %d: %s\n", i + 1, list.names[i]);
    }
    
    for (int i=0;i<list.count; i++) {
        free(list.names[i]);
        list.names[i] = NULL;
    }
    free(list.names);
    list.names = NULL;
    return 0;
}

// Done!
void allocateMemory(void** ptr, size_t size){
    *ptr = malloc(size);
    if(*ptr == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }
}
int main(void){ 
    int* arr = NULL;
    allocateMemory((void**)&arr, 20*sizeof(int));
    for(int i = 0; i < 20; i++){
        arr[i] = (i+1)*2;
        printf("\n%d", arr[i]);
    }
    printf("\n");
    free(arr);
    arr = NULL;
    printf("\n------------------------------------------------\n");
    nameListMain();
    printf("\n------------------------------------------------\n");
    mainMatrix();
    printf("\n------------------------------------------------\n");
    mainMatrixBetter();
    printf("\n------------------------------------------------\n"); 

    Matrix a, b, c, iden;
    MatrixStatus status;

    // Create Matrix
    status = matrix_create(2, 3, &a);
    if(status != MATRIX_SUCCESS){
        printf("Error creating matrix A: %d\n", status);
        return 1;
    }
    matrix_set(&a, 0, 0, 1.0);
    matrix_set(&a, 0, 1, 2.0);
    matrix_set(&a, 0, 2, 3.0);
    matrix_set(&a, 1, 0, 4.0);
    matrix_set(&a, 1, 1, 5.0);
    matrix_set(&a, 1, 2, 6.0);


    status = matrix_create(3, 2, &b);
    if(status != MATRIX_SUCCESS){
         printf("Error creating matrix B: %d\n", status);
        return 1;
    }
    matrix_set(&b, 0, 0, 7.0);
    matrix_set(&b, 0, 1, 8.0);
    matrix_set(&b, 1, 0, 9.0);
    matrix_set(&b, 1, 1, 10.0);
    matrix_set(&b, 2, 0, 11.0);
    matrix_set(&b, 2, 1, 12.0);



     // Multiply matrices
    status = matrix_multiply(&a, &b, &c);
     if (status != MATRIX_SUCCESS) {
        printf("Error Multiplying matrix: %d\n", status);
        matrix_destroy(&a);
        matrix_destroy(&b);
        return 1;
    }
    printf("Matrix A:\n");
    matrix_print(&a);
    printf("Matrix B:\n");
    matrix_print(&b);
    printf("A * B:\n");
    matrix_print(&c);
     matrix_destroy(&c);

     // Transpose
     status = matrix_transpose(&a, &c);
      if (status != MATRIX_SUCCESS) {
        printf("Error Transposing matrix: %d\n", status);
         matrix_destroy(&a);
         matrix_destroy(&b);
        return 1;
    }

    printf("Transpose of Matrix A:\n");
    matrix_print(&c);
    matrix_destroy(&c);
  
   // Scalar multiplication
     status = matrix_scalar_multiply(&a, 2, &c);
     if (status != MATRIX_SUCCESS) {
        printf("Error Scalar Multiplying matrix: %d\n", status);
         matrix_destroy(&a);
         matrix_destroy(&b);
        return 1;
    }
    printf("Matrix A x 2:\n");
    matrix_print(&c);
    matrix_destroy(&c);


    // Identity Matrix
    status = matrix_identity(3,&iden);
    if (status != MATRIX_SUCCESS) {
      printf("Error creating Identity matrix: %d\n", status);
        matrix_destroy(&a);
        matrix_destroy(&b);
        return 1;
    }
    printf("Identity Matrix:\n");
    matrix_print(&iden);
    matrix_destroy(&iden);


    // Clean up
    matrix_destroy(&a);
    matrix_destroy(&b);
    
    return 0;
}
