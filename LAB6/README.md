#### Overview
This project demonstrates a simple implementation of the Compressed Sparse Row (CSR) format for representing sparse matrices in C. The program reads a matrix from a text file and converts it into its CSR representation. This includes arrays for row pointers, column indices, and non-zero values.

### Features
- Reading matrix dimensions and non-zero elements from a file.
- Efficient storage of sparse matrices using CSR format.
- Dynamic memory allocation for storing matrix data.
- Clear and concise code with comments for easy understanding.


### How to Run
- Ensure you have a C compiler installed on your system (like gcc).
- Compile the code using a C compiler. For example:
    ``sh
        gcc -o matrix_csr matrix_csr.c

### Run the compiled program:
    ``sh
        ./matrix_csr


### Input Format
* The input file input.txt should contain the matrix data in the following format:

- The first line should have three integers: the number of rows, the number of columns, and the number of non-zero values.
- Following lines should each contain a non-zero element in the format row_index,col_index,value. Each element should be on a new line.
- Example:

    ```sh
        3 3 4
        0,0,5.0
        0,2,8.0
        1,1,3.0
        2,1,6.0

### Output
* The program will print the CSR representation of the matrix:

- row_ptr: Array indicating the start of each row in col_idx and vals.
- col_idx: Array of column indices corresponding to each non-zero value.
- vals: Array of non-zero values from the matrix.