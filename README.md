# MatrixOOP

`S21Matrix` is a class that allows you to perform operations on matrices. The capabilities of the class include:

- Addition of matrix A with matrix B
- Subtraction of matrix B from matrix A
- Multiplication of matrix A by matrix B
- Multiplication of matrix A by a number
- Transposition of a matrix
- Calculation of the determinant of a matrix
- Calculation of the matrix of algebraic complements
- Calculation of the inverse matrix

### How to Use

1. Create an object of the `S21Matrix` class, specifying the number of rows and columns of the matrix.
    
    ```cpp
    S21Matrix matrix(rows, cols);
    
    ```
    
2. Perform operations on the matrix using the available methods of the class.
    
    ```cpp
    matrix.SumMatrix(other); // Addition of matrices
    matrix.SubMatrix(other); // Subtraction of matrices
    matrix.MulMatrix(other); // Multiplication of matrices
    matrix.MulNumber(num); // Multiplication of matrix by a number
    matrix.Transpose(); // Transposition of the matrix
    double determinant = matrix.Determinant(); // Calculation of the determinant of the matrix
    S21Matrix complements = matrix.CalcComplements(); // Calculation of the matrix of algebraic complements
    S21Matrix inverse = matrix.InverseMatrix(); // Calculation of the inverse matrix
    
    ```
    
3. Check the validity of the matrix using the `IsValid()` method.
    
    ```cpp
    if (matrix.IsValid()) {
        // Matrix is valid
    } else {
        // Matrix is invalid
    }
    
    ```
    
4. Get the number of rows and columns of the matrix using the `get_rows()` and `get_cols()` methods.
    
    ```cpp
    int rows = matrix.get_rows(); // Number of rows
    int cols = matrix.get_cols(); // Number of columns
    
    ```
    

### Overloaded Operators

The `S21Matrix` class also overloads some operators for convenience:

- `==` and `!=` - Equality and inequality comparison of matrices
- `+` and `` - Addition and subtraction of matrices
- `` - Multiplication of matrix by a number or by another matrix

### Printing the Matrix

The matrix can be printed to the screen using the `<<` operator.

```cpp
std::cout << matrix;

```
