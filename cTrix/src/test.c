#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void** data;
    int size;
} StaticArray;

StaticArray* initStaticArray(int n) {
    StaticArray* array = (StaticArray*)malloc(sizeof(StaticArray));
    if (array == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    array->data = (void**)calloc(n, sizeof(void*));
    if (array->data == NULL) {
        perror("calloc failed");
        free(array);
        exit(EXIT_FAILURE);
    }
    array->size = n;
    return array;
}

void* get_at(StaticArray* array, int i) {
    if (array == NULL) {
        fprintf(stderr, "Error: Array is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (i < 0 || i >= array->size) {
        fprintf(stderr, "IndexError: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return array->data[i];
}

void set_at(StaticArray* array, int i, void* value) {
    if (array == NULL) {
        fprintf(stderr, "Error: Array is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (i < 0 || i >= array->size) {
        fprintf(stderr, "IndexError: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    array->data[i] = value;
}

void free_static_array(StaticArray* array) {
    if (array != NULL) {
        free(array->data);
        free(array);
    }
}

typedef struct {
    char* name;
    char* birthday;
} Student;

Student* student_birthday_match(Student* students, int n) {
    StaticArray* records = initStaticArray(n);
    if (records == NULL) {
        return NULL; // Handle allocation failure
    }

    for (int k = 0; k < n; ++k) {
        char* bday1 = students[k].birthday;
        for (int i = 0; i < k; ++i) {
            Student* recorded_student = (Student*)get_at(records, i);
            if (recorded_student != NULL) {
                char* bday2 = recorded_student->birthday;
                if (strcmp(bday1, bday2) == 0) {
                    Student* result = (Student*)malloc(2 * sizeof(Student));
                    if (result == NULL) {
                        perror("malloc failed");
                        free_static_array(records);
                        return NULL;
                    }
                    result[0] = students[k];
                    result[1] = *recorded_student;
                    free_static_array(records);
                    return result;
                }
            }
        }
        set_at(records, k, &students[k]);
    }
    free_static_array(records);
    return NULL;
}

int main(void) {
    Student students[] = {
        {"Alice", "01-01"},
        {"Bob", "02-01"},
        {"Charlie", "01-01"},
        {"David", "03-01"},
        {"someguy","02-01"}
    };
    int n = sizeof(students) / sizeof(Student);

    Student* match = student_birthday_match(students, n);
    if (match) {
        printf("Match found: %s and %s\n", match[0].name, match[1].name);
        free(match);
    } else {
        printf("No match found.\n");
    }
    
    return 0;
}

