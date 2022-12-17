#include "s21_matrix_oop.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ft_unuased(num) (void)(num)

std::ostream &operator<<(std::ostream &os, S21Matrix const &other) {
  int n_row = other.get_rows();
  int n_col = other.get_cols();
  if (n_row >= 0 && n_col >= 0) {
    os << "row: " << n_row << std::endl;
    os << "col: " << n_col << std::endl;
    os.precision(7);

    if (n_row >= 0 || n_col >= 0) {
      for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_col; ++j) {
          os << std::fixed << other(i, j) << " ";
        }
        os << std::endl;
      }
    }
  }

  return (os);
}

// -------------------------------------------------------

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// -------------------------------------------------------

S21Matrix::S21Matrix(int row_, int cols)
    : rows_(row_), cols_(cols), matrix_(CreateMatrix(rows_, cols_)) {}

// -------------------------------------------------------

S21Matrix::S21Matrix(S21Matrix const &other)
    : rows_(other.rows_), cols_(other.cols_),
      matrix_(CreateMatrix(rows_, cols_)) {

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator=(S21Matrix const &other) {
  if (this != &other && other.matrix_) {
    Destroy();
    Resize(other.rows_, other.cols_);

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  return *this;
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    matrix_ = FreeMatrix(matrix_, rows_);
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
  }

  return *this;
}

// -------------------------------------------------------

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
  }
}

// -------------------------------------------------------

S21Matrix::~S21Matrix() { Destroy(); }

// -------------------------------------------------------

double &S21Matrix::operator()(int row_, int col_) const {
  if (row_ < 0 || col_ < 0 || row_ > rows_ || col_ > cols_) {
    throw "[ERROR] index error ";
  }

  return matrix_[row_][col_];
}

// -------------------------------------------------------

double &S21Matrix::operator()(int row_, int col_) {
  if ((row_ < 0 || col_ < 0) || (row_ >= rows_ || col_ >= cols_)) {
    throw "[ERROR] index error ";
  }

  return matrix_[row_][col_];
}

// -------------------------------------------------------

bool S21Matrix::IsValid() const {
  int is_valid = 1;
  if (matrix_ == nullptr || (rows_ <= 1 && cols_ <= 1)) {
    is_valid = 0;
  }

  return is_valid;
}

// -------------------------------------------------------

bool S21Matrix::Resize(int row, int col) {
  bool is_success = 0;

  if (row >= 0 && col >= 0) {
    if (matrix_) {
      matrix_ = FreeMatrix(matrix_, rows_);
      rows_ = 0;
      cols_ = 0;
    }
    rows_ = row;
    cols_ = col;
    matrix_ = CreateMatrix(rows_, cols_);
    is_success = true;
  } else {
    throw "[ERROR] row or col is not valid";
  }

  return is_success;
}

// -------------------------------------------------------

int S21Matrix::get_rows() const { return rows_; }

// -------------------------------------------------------

int S21Matrix::get_cols() const { return cols_; }

// -------------------------------------------------------

bool S21Matrix::EqMatrix(S21Matrix const &other) const {
  bool is_equal = 0;

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    is_equal = 1;
    for (int i = 0; i < rows_ && matrix_ && other.matrix_ && is_equal; ++i) {
      for (int j = 0; j < cols_ && is_equal; ++j) {
        if (((matrix_[i][j]) - (other.matrix_[i][j])) > 1e-7) {
          is_equal = 0;
        }
      }
    }
  }

  return is_equal;
}

// -------------------------------------------------------

void S21Matrix::SumMatrix(S21Matrix const &other) {
  if (IsValid() && other.IsValid()) {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
        }
      }
    } else {
      throw "[ERROR] row or col is not equal";
    }
  } else {
    throw "[ERROR] row or col is not valid";
  }
}

// -------------------------------------------------------

void S21Matrix::SubMatrix(S21Matrix const &other) {
  if (IsValid() && other.IsValid()) {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          matrix_[i][j] -= other.matrix_[i][j];
        }
      }
    } else {
      throw "[ERROR] row or col is not equal";
    }
  } else {
    throw "[ERROR] Matrix is not valid";
  }
}

// -------------------------------------------------------

void S21Matrix::MulNumber(double const num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

// -------------------------------------------------------

void S21Matrix::MulMatrix(S21Matrix const &other) {
  if (other.IsValid() && IsValid()) {
    if (rows_ == other.get_cols() || cols_ == other.get_rows()) {
      S21Matrix result_matrix;
      int M = 0;
      int N = 0;
      int K = 0;

      if (cols_ == other.get_rows()) {
        M = rows_;
        N = other.get_cols();
        K = cols_;
        result_matrix.Resize(M, N);
        MulMatrix(M, N, K, *this, other, result_matrix);
      } else {
        M = other.get_rows();
        N = cols_;
        K = other.get_cols();
        result_matrix.Resize(M, N);
        MulMatrix(M, N, K, other, *this, result_matrix);
      }
      *this = result_matrix;
    } else {
      throw "[ERROR] matrix 1 (cols) != matrix 2 (rows)";
    }
  } else {
    throw "[ERROR] Matrix is not valid";
  }
}

// -------------------------------------------------------

S21Matrix S21Matrix::Transpose() const {
  S21Matrix tmp_matrix(cols_, rows_);

  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      tmp_matrix(i, j) = matrix_[j][i];
    }
  }

  return tmp_matrix;
}

// -------------------------------------------------------

double S21Matrix::Determinant() const {
  double result = 1;

  if (matrix_) {
    int row = cols_;
    int col = rows_;

    if (row == col && row >= 1) {
      result = this->Determinant(matrix_, cols_);
    } else {
      throw "[ERROR] matrix is not square";
    }
  }

  return result;
}

// -------------------------------------------------------

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(3, 3);
  result(1, 1) = 2;
  int row = cols_;
  int col = rows_;

  if (row == col && row >= 2) {
    result.Resize(row, row);
    CalcComplements(result, row);
  } else {
    throw "[ERROR] Matrix is not square";
  }

  return result;
}

// -------------------------------------------------------

S21Matrix S21Matrix::InverseMatrix() const {
  int row = cols_;
  int col = rows_;
  S21Matrix tmpMatrix;

  if (matrix_ && row == col && row >= 1) {
    double d = Determinant(matrix_, row);
    if (d == 0) {
      throw "[ERROR] Determinant equal zero";
    } else {
      tmpMatrix = CalcComplements();
      tmpMatrix = tmpMatrix.Transpose();
      for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row; ++j) {
          tmpMatrix.matrix_[i][j] = tmpMatrix.matrix_[i][j] / (double)(d);
        }
      }
    }
  } else {
    throw "[ERROR] matrix is not valid";
  }

  return tmpMatrix;
}

// -------------------------------------------------------

double **S21Matrix::CreateMatrix(int rows, int columns_) const {
  double **result = nullptr;

  if (rows > 0 && columns_ > 0) {
    if (!(result = new double *[rows]())) {
      throw "[ERROR] memory leaks";
    }

    for (int i = 0; i < rows; i++) {
      if (!(result[i] = new double[columns_]())) {
        throw "[ERROR] memory leaks";
      }
    }
  }

  return result;
}

// -------------------------------------------------------

double **S21Matrix::FreeMatrix(double **arr, int rows) const {
  if (arr) {
    for (int i = 0; i < rows; i++) {
      if (arr[i]) {
        delete[] arr[i];
        arr[i] = nullptr;
      }
    }
    delete[] arr;
    arr = nullptr;
  }

  return arr;
}

// -------------------------------------------------------

void S21Matrix::Minor(double **matrix, int const x, int const y,
                      int const count) const {
  int n_x = 0;
  int n_y = 0;

  for (int i = 0; i < count; ++i) {
    if (i != x) {
      n_y = 0;

      for (int j = 0; j < count; ++j) {
        if (j != y) {
          matrix[n_x][n_y] = matrix_[i][j];
          ++n_y;
        }
      }
      ++n_x;
    }
  }
}

// -------------------------------------------------------

void S21Matrix::CalcComplements(S21Matrix &matrix_, int const count) const {
  double det = 1;
  double **mnr = CreateMatrix(count - 1, count - 1);

  for (int j = 0; j < count; ++j) {
    for (int i = 0; i < count; ++i) {
      Minor(mnr, j, i, count);
      det = (i + j) % 2 == 0 ? 1 : -1;
      matrix_.matrix_[j][i] = det * Determinant(mnr, count - 1);
    }
  }

  mnr = FreeMatrix(mnr, count - 1);
}

// -------------------------------------------------------

void S21Matrix::MulMatrix(int const rows, int const count_cols, int const cols,
                          S21Matrix const &matrix_a, S21Matrix const &matrix_b,
                          S21Matrix &matrix_c) const {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < count_cols; ++j) {
      matrix_c(i, j) = 0;
      for (int k = 0; k < cols; ++k) {
        matrix_c(i, j) += matrix_a(i, k) * matrix_b(k, j);
      }
    }
  }
}

// -------------------------------------------------------

double S21Matrix::Determinant(double **matrix, int const num) const {
  double result = 0;
  int tmp_j = 0;
  double s = 1;
  double **tmp_arr = NULL;

  if (num == 1) {
    result = matrix[0][0];
  } else if (num == 2) {
    result = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
  } else if (num > 2) {
    if (!(tmp_arr = new double *[num - 1])) {
      throw "[ERROR] memory leaks";
    }
    for (int i = 0; i < num; i++) {
      tmp_j = 0;
      for (int j = 0; j < num; j++)
        if (i != j)
          tmp_arr[tmp_j++] = matrix[j] + 1;
      result = result + s * matrix[i][0] * Determinant(tmp_arr, num - 1);
      s = -s;
    };
    delete[] tmp_arr;
  }

  return result;
}

// -------------------------------------------------------

bool S21Matrix::operator==(S21Matrix const &other) const {
  return EqMatrix(other);
}

// -------------------------------------------------------

bool S21Matrix::operator!=(S21Matrix const &other) const {
  return !(EqMatrix(other));
}

// -------------------------------------------------------

S21Matrix S21Matrix::operator-(S21Matrix const &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);

  return result;
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator-=(S21Matrix const &other) {
  this->SubMatrix(other);
  return (*this);
}

// -------------------------------------------------------

S21Matrix S21Matrix::operator+(S21Matrix const &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);

  return result;
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator+=(S21Matrix const &other) {
  this->SumMatrix(other);
  return *this;
}

// -------------------------------------------------------

S21Matrix S21Matrix::operator*(double const num) const {
  S21Matrix result(*this);
  result.MulNumber(num);

  return result;
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator*=(double const num) {
  this->MulNumber(num);
  return *this;
};

// -------------------------------------------------------

S21Matrix S21Matrix::operator*(S21Matrix const &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);

  return result;
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator*=(S21Matrix const &other) {
  this->MulMatrix(other);
  return (*this);
}

// -------------------------------------------------------

void S21Matrix::Destroy() {
  matrix_ = FreeMatrix(matrix_, rows_);
  rows_ = 0;
  cols_ = 0;
}
