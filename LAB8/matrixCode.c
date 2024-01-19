#include <stdio.h>   //Including the Standard Input/Output library
                      

#include <stdlib.h>  /*Including the Standard Library
                      This library provides functions for performing memory allocation (e.g., malloc),
                      control of dynamic storage (e.g., free), and other general utility functions.*/

#include <assert.h>  /*Including the assert library
                      This library provides the assert macro, which is used to assist with debugging.
                      It's used to test assumptions made by the program and can be used to quickly identify
                      problems by halting the program if an assertion fails.*/



// Defining a structure for the linked list node
struct Node {
    int col;           // Column index of the node
    int val;           // Value of the node
    struct Node* next; // Pointer to the next node in the list
};

// Function declarations for the program
struct Node* create_node(int col, int val);
void print(struct Node* id, FILE* output_file);
void delete_node(struct Node** row_ptr, int num_rows, int num_cols, int row, int col);
void update_node(struct Node** row_ptr, int num_rows, int num_cols, int row, int col, int new_val);
void print_matrix(struct Node** row_ptr, int num_rows, FILE* output_file, const char* title);
void tear_down(struct Node** row_ptr, int size);

int main(int argc, char* argv[]) {
    // Checking for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file and a output file 
    char* input_file_name = argv[1];
    FILE* f_ptr = fopen(input_file_name, "r");
    FILE* output_file = fopen("output.txt", "w");

    // Error handling for the file opening
    if (f_ptr == NULL || output_file == NULL) {
        printf("Error: Unable to open the file '%s'\n", input_file_name);
        if (output_file == NULL) {
            printf("Error: Unable to open the output file 'output.txt'\n");
        }
        return 1;
    }

    // Reading the matrix dimensions from the input file
    int num_rows, num_cols;
    if (fscanf(f_ptr, "%d %d\n", &num_rows, &num_cols) != 2) {
        printf("Error: Invalid dimensions in the file '%s'\n", input_file_name);
        fclose(f_ptr);
        fclose(output_file);
        return 1;
    }

    // Allocating memory for the array of row pointers
    struct Node** row_ptr = (struct Node**)calloc(num_rows, sizeof(struct Node*));

    // Reading the matrix values from the file and create nodes
    int row, col, val;
    while (fscanf(f_ptr, "%d %d %d\n", &row, &col, &val) == 3) {
        // Checking for valid row and column indices
        if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) {
            printf("Error: Invalid row or column index in the file '%s'\n", input_file_name);
            fclose(f_ptr);
            fclose(output_file);
            tear_down(row_ptr, num_rows);
            return 1;
        }

        // Creating a new node and add it to the appropriate row
        struct Node* ptr = create_node(col, val);
        if (row_ptr[row] == NULL) {
            row_ptr[row] = ptr;
        } else {
            struct Node* track = row_ptr[row];
            while (track->next != NULL) {
                track = track->next;
            }
            track->next = ptr;
        }
    }

    // Close the input file
    fclose(f_ptr);

    // Printing the initial matrix to both terminal and output file output.txt
    print_matrix(row_ptr, num_rows, output_file, "Initial Matrix:");

    // Performing delete and update operations on the matrix 
    delete_node(row_ptr, num_rows, num_cols, 0, 2);
    update_node(row_ptr, num_rows, num_cols, 1, 1, 42);

    // Printing the modified matrix to both terminal and output file output.txt
    print_matrix(row_ptr, num_rows, output_file, "\nModified Matrix:");

    // Closing the output file 
    fclose(output_file);

    // Free the allocated memory for the matrix
    tear_down(row_ptr, num_rows);

    return 0;
}

// Function to create a new node for the linked list and return a pointer to it
struct Node* create_node(int col, int val) {
    // Dynamically allocate memory for a new Node struct.
    // The size of the allocation is the size of a Node structure.
    // This memory allocation is necessary for adding new elements to the linked list.
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));

    // Set the column index of the new node.
    // This index indicates where the node is positioned within its respective row in the matrix.
    ptr->col = col;

    // Set the value of the new node.
    // This value is the actual data the node is storing, representing an element in the matrix.
    ptr->val = val;

    // Initialize the 'next' pointer of the node to NULL.
    // This indicates that currently, this node does not point to any other node in the list.
    // When inserted into the linked list, this pointer will be updated to link to the next node.
    ptr->next = NULL;

    // Return a pointer to the newly created node.
    // This pointer will be used to add this node into the linked list at the correct position.
    return ptr;
}


// Function to print a node's data to both the terminal and the output file 'output.txt'
void print(struct Node* id, FILE* output_file) {
    // The function takes two parameters: a pointer to a Node (id) and a file pointer (output_file).
    // Print the column index and value of the node to the terminal.
    // This provides a visual output on the console for the user.
    printf("col: %d, val: %d\n", id->col, id->val);

    // Similarly, print the same column index and value to the output file.
    // This records the node's data in 'output.txt'.
    fprintf(output_file, "col: %d, val: %d\n", id->col, id->val);
}


// Function to delete a node from the linked list 
void delete_node(struct Node** row_ptr, int num_rows, int num_cols, int row, int col) {
    // First, check if the specified row and column indices are within the valid range.
    // If they are not, print an error message and exit the function.
    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) {
        printf("Error: Invalid row or column index for deletion\n");
        return;
    }

    // Traverse the linked list of the specified row to find the node with the specified column index.
    struct Node* current = row_ptr[row]; // Current node being examined
    struct Node* previous = NULL;        // Previous node in the list

    // Loop through the nodes in the linked list
    while (current != NULL) {
        // Check if the current node is the one to be deleted
        if (current->col == col) {
            // If the node to be deleted is the first node in the list
            if (previous == NULL) {
                row_ptr[row] = current->next; // Update the head of the list to the next node
            } else {
                // If the node to be deleted is not the first node
                previous->next = current->next; // Bypass the current node in the list
            }
            free(current); // Free the memory allocated for the node
            return; // Return after deletion to end the function
        }
        // Move to the next node, keeping track of the current and previous nodes
        previous = current;
        current = current->next;
    }

    // If no node with the specified column index is found in the row, print an error message.
    printf("Error: Node not found for deletion\n");
}


// Function to update a node's value in the linked list 
void update_node(struct Node** row_ptr, int num_rows, int num_cols, int row, int col, int new_val) {
    // Check if the specified row and column indices are within the valid range
    // If they are not, print an error message and exit the function
    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) {
        printf("Error: Invalid row or column index for update\n");
        return;
    }

    // Traverse the linked list of the specified row to find the node with the specified column index
    struct Node* current = row_ptr[row];
    while (current != NULL) {
        // If the node with the matching column index is found, update its value
        if (current->col == col) {
            current->val = new_val;
            return; // Return after updating to end the function
        }
        current = current->next; // Move to the next node in the list if not found yet
    }

    // If no node with the specified column index is found in the row, print an error message
    printf("Error: Node not found for update\n");
}


// Function to print the matrix to both the terminal and the output file 'output.txt'
void print_matrix(struct Node** row_ptr, int num_rows, FILE* output_file, const char* title) {
    // First, print the title of the matrix section (like 'Initial Matrix:' or 'Modified Matrix:')
    printf("%s\n", title);               // Print to the terminal
    fprintf(output_file, "%s\n", title); // Print to the output file

    // Iterate through each row of the matrix
    for (int i = 0; i < num_rows; i++) {
        // Print the row index to both terminal and output file
        printf("row: %d\n", i);
        fprintf(output_file, "row: %d\n", i);

        // Start at the first node (if any) in this row's linked list
        struct Node* track = row_ptr[i];
        
        // Traverse the linked list for this row
        while (track != NULL) {
            // Print the current node's data (column index and value) to both terminal and output file
            print(track, output_file); // 'print' function handles the printing
            track = track->next;       // Move to the next node in the list
        }

        // Print a newline for separation between rows
        printf("\n");
        fprintf(output_file, "\n");
    }
}

// Function to free the allocated memory for the matrix
void tear_down(struct Node** row_ptr, int size) {
    // Iterate over each row in the array of row pointers
    for (int i = 0; i < size; i++) {
        struct Node* current = row_ptr[i]; // Start at the head of the row's linked list
        // Traverse the linked list and free each node
        while (current != NULL) {
            struct Node* temp = current; // Temporarily store the current node
            current = current->next;     // Move to the next node in the list
            free(temp);                  // Free the memory of the current node
        }
        row_ptr[i] = NULL; // Set the row pointer to NULL after freeing its linked list
    }
    free(row_ptr); // Finally, free the memory of the array of row pointers itself
}
