#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#define DOUBLE_STR_NUM 200

#define SUCCESS 1
#define FAILURE 0

#include <exception>
#include <iostream>

/*! \class S21Matrix
 *  \brief Working with matrices.
 *
 *  Detailed -> This class allows you to perform some operations on matrices:
 *                  Addition of matrix A with matrix B. Subtraction of matrix B
 *                  from matrix A. Multiplication of
 *                  matrix A by matrix B. ...
 */
class S21Matrix {
public:
  S21Matrix();
  explicit S21Matrix(int row_, int cols_);
  S21Matrix(S21Matrix const &other);
  S21Matrix(S21Matrix &&other);

  ~S21Matrix();

  /**
   * @brief Checks matrices for equality among themselves.
   *
   * @param other -> Another matrix.
   *
   * @return -> (bool) True | False
   */
  bool EqMatrix(S21Matrix const &other) const;

  /**
   * @brief Adds the second matrix to the current one.
   *
   * @param other -> Another matrix.
   */
  void SumMatrix(S21Matrix const &other);

  /**
   * @brief Subtracts another one from the current matrix.
   *
   * @param other -> Another matrix.
   */
  void SubMatrix(S21Matrix const &other);

  /**
   * @brief Multiplies the current matrix by a number.
   *
   * @param num -> (double) Number.
   */
  void MulNumber(double const num);

  /**
   * @brief Multiplies the current matrix by the second one.
   *
   * @param other-> Another matrix.
   */
  void MulMatrix(S21Matrix const &other);

  /**
   * @brief Creates a new transposed matrix from the current one and returns it.
   *
   * @return -> (S21Matrix) matrix.
   */
  S21Matrix Transpose() const;

  /**
   * @brief Calculates and returns the determinant of the current matrix.
   *
   * @return  -> (double) Determinant.
   */
  double Determinant() const;

  /**
   * @brief Calculates the matrix of algebraic complements
   *            ofthe current matrix and returns it.
   *
   * @return -> (S21Matrix) matrix.
   */
  S21Matrix CalcComplements() const;

  /**
   * @brief Calculates and returns the inverse matrix.
   *
   * @return -> (S21Matrix) matrix.
   */
  S21Matrix InverseMatrix() const;

  /* assignment operator and move operator */
  S21Matrix &operator=(S21Matrix const &other);
  S21Matrix &operator=(S21Matrix &&other);

  /* Overloaded operators */
  bool operator!=(S21Matrix const &other) const;
  bool operator==(S21Matrix const &other) const;
  S21Matrix operator-(S21Matrix const &other) const;
  S21Matrix &operator-=(S21Matrix const &other);
  S21Matrix operator+(S21Matrix const &other) const;
  S21Matrix &operator+=(S21Matrix const &other);
  S21Matrix operator*(double const num) const;
  S21Matrix &operator*=(double const num);
  S21Matrix operator*(S21Matrix const &other) const;
  S21Matrix &operator*=(S21Matrix const &other);

  double &operator()(int row_, int col_) const;
  double &operator()(int row_, int col_);

  /* print matrix */
  friend std::ostream &operator<<(std::ostream &os, S21Matrix const &other);

  /**
   * @brief Checking the validity of the matrix.
   *
   * @return (bool) True | False
   */
  bool IsValid() const;

  /**
   * @brief Changing the size of the matrix. (mutator)
   *
   * @param row -> Rows in the matrix.
   * @param col -> Cols in the matirx.
   *
   * @return -> (bool) True | False
   */
  bool Resize(int row, int col);

  /* Accessor rows_ and cols_ field */
  int get_rows() const;
  int get_cols() const;

private:
  /* Helper functions */
  double **CreateMatrix(int rows, int columns_) const;
  double **FreeMatrix(double **arr, int rows) const;
  void MulMatrix(int const rows, int const count_cols, int const cols,
                 S21Matrix const &matrix_a, S21Matrix const &matrix_b,
                 S21Matrix &matrix_c) const;
  double Determinant(double **matrix_, int const num) const;
  void Minor(double **matrix, int const x, int const y, int const count) const;
  void CalcComplements(S21Matrix &matrix_, int const count) const;
  void Destroy();

private:
  int rows_;
  int cols_;
  double **matrix_;
};

#endif // S21_MATRIX_OOP_H_
