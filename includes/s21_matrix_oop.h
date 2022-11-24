#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#define DOUBLE_STR_NUM 200

#define SUCCESS 1
#define FAILURE 0

#include <iostream>

class S21Matrix {
public:
  S21Matrix();
  S21Matrix(int row_, int cols_);
  S21Matrix(S21Matrix const &other);
  S21Matrix(S21Matrix const &&other);
  S21Matrix &operator=(S21Matrix const &other_);
  S21Matrix &operator=(S21Matrix &&other_);
  virtual ~S21Matrix();

  friend std::ostream &operator<<(std::ostream &os, S21Matrix const &other_);
  double operator()(int row_, int col_) const;
  double &operator()(int row_, int col_);

  bool eqMatrix(S21Matrix const &other_);
  void sumMatrix(S21Matrix const &other_);
  void subMatrix(S21Matrix const &other_);
  void mulNumber(double const num_);
  void mulMatrix(S21Matrix const &other_);
  S21Matrix transpose();
  double determinant();
  S21Matrix calcComplements();
  S21Matrix inverseMatrix();

  bool operator==(S21Matrix const &other_);
  S21Matrix operator-(S21Matrix const &other_);
  void operator-=(S21Matrix const &other_);
  S21Matrix operator+(S21Matrix const &other_);
  void operator+=(S21Matrix const &other_);
  S21Matrix operator*(double num_);
  void operator*=(double num_);
  S21Matrix operator*(S21Matrix const &other_);
  void operator*=(S21Matrix const &other_);

  bool isValid() const;
  bool resize(int row_, int col_);
  int rows() const;
  int cols() const;

  void print() const;
  std::string doubleToString(double num_);

private:
  double **createArrayDeep2(int rows_, int columns_);
  double **freeArrayDeep2(double **arr_, int rows_);

  void mult(int m_, int n_, int k_, S21Matrix const &a_, S21Matrix const &b_,
            S21Matrix &c_);
  double determinant(double **matrix_, int num_);
  void minor(double **B_, int x_, int y_, int N_);
  void calcComplements(S21Matrix &matrix_, int N_);

private:
  int m_rows;
  int m_cols;
  double **m_matrix;
};

#endif // S21_MATRIX_OOP_H_
