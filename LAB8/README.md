## Description

This C program manages a matrix stored as an array of linked lists, where each array element corresponds to a row and each linked list represents the non-zero elements in that row. It supports dynamic interaction with the matrix through functionalities like deleting and updating nodes. The program reads the matrix data from a file (`matrix.txt`), whose name is passed as a command-line argument, and prints both the initial and the modified matrices to the console and an output file(`output.txt`).

## How to Compile

1. Open your terminal or command prompt.

2. Navigate to the directory containing the `matrixHW.c` source code file.

3. Compile the program using the `gcc` compiler:

   ```bash
   gcc matrixHW.c -o matrixHW

4. This command compiles the matrixHW.c source code and generates an executable named matrixHW.

5. Ensure you have the input file named matrix.txt in the same directory as the compiled executable.

6. Run the program with the input file as follows:

    ./matrixHW matrix.txt

7. The program will display the initial matrix and the modified matrix (if applicable) in the terminal.

8. Also, the modified matrix can be found in an output file named `output.txt` in the same directory.


## Input File Format

1. The matrix.txt input file should have the following format:

    <Number of Rows> <Number of Columns>
    <Row Index> <Column Index> <Value>
    <Row Index> <Column Index> <Value>
...


## Functions

1. delete_node: Given a row and a column pair, this function finds and deletes the corresponding node from the linked list.

2. update_node: Given a row and a column pair, it finds and updates the value of the corresponding node in the linked list.

3. print_linked_list:  Prints the entire linked list representation of the matrix on the screen and to a specified output file.

4. tear_down: Frees the memory used by the linked lists to prevent memory leaks.
