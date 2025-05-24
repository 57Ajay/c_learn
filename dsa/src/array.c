#include "all.h"
#include <stdio.h>
#include <stdlib.h>

void print_arr(int arr[], int size);

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void selection_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void insertion_sort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            // printf("Arr in while loop: ");
            // print_arr(arr, size);
        }

        arr[j + 1] = key;
        // printf("Arr out: ");
        // print_arr(arr, size);
    }
}

int partition(int arr[], int l, int h) {
    int pivot = arr[h];
    int i = l - 1;
    for (int j = l; j < h; j++) {
        if (arr[j] <= pivot) {
            i += 1;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[h];
    arr[h] = temp;
    return i + 1;
}

void quick_sort(int arr[], int size, int low, int high) {
    if (low < high) {
        int pivot_index = partition(arr, low, high);
        quick_sort(arr, size, low, pivot_index - 1);
        quick_sort(arr, size, pivot_index + 1, high);
    }
}

void print_arr(int arr[], int size) {
    printf("\n----------Printing array----------\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n----------Array Printed----------\n");
}

int max(int arr[], int size) {
    int max = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void counting_sort(int arr[], int size) {
    int maxVal = max(arr, size);
    int *countArr = calloc(maxVal + 1, sizeof(int));
    for (int i = 0; i < size; i++) {
        int countArrIndex = arr[i];
        countArr[countArrIndex]++;
    }
    int arrIdx = 0;
    for (int i = 0; i <= maxVal; i++) {
        for (int j = 0; j < countArr[i]; j++) {
            arr[arrIdx] = i;
            arrIdx++;
        }
        countArr[i] = 0;
    }
    free(countArr);
}

int get_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void counting_sort_by_digit(int arr[], int size, int place) {
    int output[size];
    int count[10] = {0};

    for (int i = 0; i < size; i++) {
        int digit = (arr[i] / place) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // this is stable sort
    for (int i = size - 1; i >= 0; i--) {
        int digit = (arr[i] / place) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(int arr[], int size) {
    int max = get_max(arr, size);
    for (int place = 1; max / place > 0; place *= 10) {
        counting_sort_by_digit(arr, size, place);
    }
}

int arr_sortings() {
    int arr1[] = {2, 3, 0, 2, 3, 2};
    int len = sizeof(arr1) / sizeof(arr1[0]);
    // bubble_sort(arr1, len);
    // selection_sort(arr1, len);
    // insertion_sort(arr1, len);
    // quick_sort(arr1, len, 0, len - 1);
    // counting_sort(arr1, len);
    radix_sort(arr1, len);
    print_arr(arr1, len);
    return 69;
}
