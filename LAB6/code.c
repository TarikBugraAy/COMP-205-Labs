
//Tarık Buğra Ay 
#include <stdio.h>
#include <stdlib.h>

// Function to print an array
void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    // Open the file "input.txt" for reading
    FILE* p_file = fopen("input.txt", "r");

    // Variables to store matrix dimensions and number of non-zero values
    int num_rows, num_cols, num_vals;

    if (p_file != NULL) {
        // Read matrix dimensions and non-zero count from the file
        fscanf(p_file, "%d %d %d", &num_rows, &num_cols, &num_vals);

        // Allocate memory for arrays to store CSR representation
        int* row_ptr = (int*)malloc((num_rows + 1) * sizeof(int));
        int* col_idx = (int*)malloc(num_vals * sizeof(int));
        float* vals = (float*)malloc(num_vals * sizeof(float));

        // Initialize variables for processing the matrix
        int curr_row = 0;
        int row_read;
        row_ptr[0] = 0;

        // Read matrix values from the file
        for (int i = 0; i < num_vals; i++) {
            fscanf(p_file, "%d,%d,%f", &row_read, &col_idx[i], &vals[i]);

            // Update row_ptr when a new row is encountered
            if (row_read != curr_row) {
                row_ptr[row_read] = i;
                curr_row = row_read;
            }
        }

        // Set the last element of row_ptr to indicate the end of the last row
        row_ptr[num_rows] = num_vals;

        // Print the CSR representation
        printf("row_ptr:\n");
        print_array(row_ptr, num_rows + 1);

        printf("col_idx:\n");
        print_array(col_idx, num_vals);

        printf("vals:\n");
        for (int i = 0; i < num_vals; i++)
            printf("%.1f ", vals[i]);
        printf("\n");

        // Free allocated memory
        free(row_ptr);
        free(col_idx);
        free(vals);

        // Set pointers to NULL
        row_ptr = NULL;
        col_idx = NULL;
        vals = NULL;

        // Close the file
        fclose(p_file);
    }

    return 0;
}
