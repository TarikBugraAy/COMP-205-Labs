//Tarık Buğra AY 042101100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void filter_greater_than(int arr[], int* pivot, int filtered[], int* size) {
    int filteredCount = 0;
    for (int i = 0; i < SIZE; i++)
        if (arr[i] > *pivot)
            filtered[filteredCount++] = arr[i];

    *size = filteredCount;
}

int main() {
    int arr[SIZE] = {5, 9, 9, 56, 6, 8, 9, 8, 9, 10};

    srand(time(NULL));

    int pivotIndex = rand() % SIZE;
    int* ptr = &arr[pivotIndex];

    printf("Pivot chosen: %d\n", *ptr);

    int filtered[SIZE] = {0};
    int size;

    filter_greater_than(arr, ptr, filtered, &size);

    for (int i = 0; i < size; i++)
        printf("filtered[%d]: %d\n", i, filtered[i]);

    return 0;
}
