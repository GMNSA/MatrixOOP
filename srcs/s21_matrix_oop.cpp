#include "s21_matrix_oop.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ft_unuased(num) (void)(num)

S21Matrix::S21Matrix()
    : m_rows(0), m_cols(0), m_matrix(createArrayDeep2(m_rows, m_cols)) {}

// -------------------------------------------------------

S21Matrix::S21Matrix(int row_, int cols_)
    : m_rows(row_), m_cols(cols_), m_matrix(createArrayDeep2(m_rows, m_cols)) {}

// -------------------------------------------------------

S21Matrix::S21Matrix(S21Matrix const &other_)
    : m_rows(other_.m_rows), m_cols(other_.m_cols),
      m_matrix(createArrayDeep2(m_rows, m_cols)) {

  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_matrix[i][j] = other_.m_matrix[i][j];
    }
  }
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator=(S21Matrix const &other_) {

  if (this != &other_ && other_.m_matrix) {
    resize(other_.m_rows, other_.m_cols);

    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_cols; ++j) {
        m_matrix[i][j] = other_.m_matrix[i][j];
      }
    }
  }

  return (*this);
}

// -------------------------------------------------------

S21Matrix &S21Matrix::operator=(S21Matrix &&other_) {
  std::swap(m_rows, other_.m_rows);
  std::swap(m_cols, other_.m_cols);
  std::swap(m_matrix, other_.m_matrix);

  return (*this);
}

// -------------------------------------------------------

S21Matrix::S21Matrix(S21Matrix const &&other_)
    : m_rows(std::move(other_.m_rows)), m_cols(std::move(other_.m_cols)),
      m_matrix(std::move(other_.m_matrix)) {
  std::cout << "move constructor" << std::endl;
}

// -------------------------------------------------------

S21Matrix::~S21Matrix() {
  m_matrix = freeArrayDeep2(m_matrix, m_rows);
  m_rows = 0;
  m_cols = 0;
}

// -------------------------------------------------------

std::ostream &operator<<(std::ostream &os, S21Matrix const &other_) {
  int nRow = other_.rows();
  int nCol = other_.cols();
  if (nRow >= 0 && nCol >= 0) {
    os << "row: " << nRow << std::endl;
    os << "col: " << nCol << std::endl;
    os.precision(7);

    if (nRow >= 0 || nCol >= 0) {
      for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j) {
          os << std::fixed << other_(i, j) << " ";
        }
        os << std::endl;
      }
    }
  }

  return (os);
}

// -------------------------------------------------------

double S21Matrix::operator()(int row_, int col_) const {
  double res = 0;
  if (row_ >= 0 && col_ >= 0 && row_ < m_rows && col_ < m_cols) {
    res = m_matrix[row_][col_];
  } else {
    std::cerr << "index error _ " << __LINE__ << std::endl;
    throw "[ERROR] index error ";
  }
  return (res);
}

// -------------------------------------------------------

double &S21Matrix::operator()(int row_, int col_) {
  if ((row_ < 0 || col_ < 0) || (row_ >= m_rows || col_ >= m_cols)) {
    std::cerr << "index error _ " << __LINE__ << std::endl;
    throw "[ERROR] index error ";
  }

  return (m_matrix[row_][col_]);
}

// -------------------------------------------------------

bool S21Matrix::isValid() const {
  int isValid = 1;
  if (m_matrix == nullptr || (m_rows == 0 && m_cols == 0)) {
    isValid = 0;
  }

  return (isValid);
}

// -------------------------------------------------------

bool S21Matrix::resize(int row_, int col_) {
  bool isSuccess = 0;
  if (row_ >= 0 && col_ >= 0) {
    if (m_matrix) {
      m_matrix = freeArrayDeep2(m_matrix, m_rows);
      m_rows = 0;
      m_cols = 0;
    }
    m_rows = row_;
    m_cols = col_;
    m_matrix = createArrayDeep2(m_rows, m_cols);
    isSuccess = 1;
  } else {
    throw "[ERROR] row, col is not valid";
  }

  return (isSuccess);
}

// -------------------------------------------------------

int S21Matrix::rows() const { return (m_rows); }

// -------------------------------------------------------

int S21Matrix::cols() const { return (m_cols); }

// -------------------------------------------------------

void S21Matrix::print() const {
  std::cout << "row: " << m_rows << std::endl;
  std::cout << "col: " << m_cols << std::endl;

  if (m_rows > 0 || m_cols > 0) {
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_cols; ++j) {
        std::cout << m_matrix[i][j];
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

// -------------------------------------------------------

bool S21Matrix::eqMatrix(S21Matrix const &other_) {
  bool isEqual = 0;
  if (m_rows == other_.m_rows && m_cols == other_.m_cols) {
    isEqual = 1;
    for (int i = 0; i < m_rows && m_matrix && other_.m_matrix && isEqual; ++i) {
      for (int j = 0; j < m_cols && isEqual; ++j) {
        if (doubleToString(m_matrix[i][j]) !=
            doubleToString(other_.m_matrix[i][j])) {
          isEqual = 0;
        }
      }
    }
  }

  return (isEqual);
}

// -------------------------------------------------------

void S21Matrix::sumMatrix(S21Matrix const &other_) {
  if (isValid() && other_.isValid()) {
    if (m_rows == other_.m_rows && m_cols == other_.m_cols) {
      for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
          m_matrix[i][j] = m_matrix[i][j] + other_.m_matrix[i][j];
        }
      }
    } else {
      throw "[ERROR] row and col is not equal";
    }
  } else {
    throw "[ERROR] row, col is not valid";
  }
}

// -------------------------------------------------------

void S21Matrix::subMatrix(S21Matrix const &other_) {
  if (isValid() && other_.isValid()) {
    if (m_rows == other_.m_rows && m_cols == other_.m_cols) {
      for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
          m_matrix[i][j] -= other_.m_matrix[i][j];
        }
      }
    } else {
      throw "[ERROR] row and col is not equal";
    }
  } else {
    throw "[ERROR] row, col is not valid";
  }
}

// -------------------------------------------------------

void S21Matrix::mulNumber(double const num_) {
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_matrix[i][j] *= num_;
    }
  }
}

// -------------------------------------------------------

void S21Matrix::mulMatrix(S21Matrix const &other_) {
  if (other_.isValid() && isValid()) {

    if ((m_cols == other_.rows()) || (m_rows == other_.cols())) {
      S21Matrix tmp;
      int M = 0;
      int N = 0;
      int K = 0;
      if (m_cols == other_.rows()) {
        M = m_rows;
        N = other_.cols();
        K = m_cols;
        tmp.resize(M, N);
        mult(M, N, K, *this, other_, tmp);
      } else {
        M = other_.rows();
        N = m_cols;
        K = other_.cols();
        tmp.resize(M, N);
        mult(M, N, K, *this, other_, tmp);
      }
      *this = tmp;
    } else {
      throw "[ERROR] matrix 1 (cols) != matrix 2 (rows)";
    }
  } else {
    throw "[ERROR] Matrix is not valid";
  }
}

// -------------------------------------------------------

S21Matrix S21Matrix::transpose() {
  S21Matrix tmpMatrix(m_cols, m_rows);

  for (int i = 0; i < m_cols; i++) {
    for (int j = 0; j < m_rows; j++) {
      tmpMatrix(i, j) = m_matrix[j][i];
    }
  }

  return (tmpMatrix);
}

// -------------------------------------------------------

double S21Matrix::determinant() {
  double result = 1;

  if (m_matrix) {
    int row = m_cols;
    int col = m_rows;

    if (row == col && row >= 1) {
      result = this->determinant(m_matrix, m_cols);
    } else {
      throw "[ERROR] matrix is not valid";
    }
  }

  return (result);
}

// -------------------------------------------------------

S21Matrix S21Matrix::calcComplements() {
  S21Matrix result(3, 3);
  result(1, 1) = 2;
  int row = m_cols;
  int col = m_rows;

  if (row == col && row >= 2) {
    result.resize(row, row);
    calcComplements(result, row);
  } else {
    throw "[ERROR] Matrix is not square";
  }

  return (result);
}

// -------------------------------------------------------

S21Matrix S21Matrix::inverseMatrix() {
  int row = m_cols;
  int col = m_rows;
  S21Matrix tmpMatrix;

  if (m_matrix && row == col && row >= 1) {
    double d = determinant(m_matrix, row);
    if (d == 0) {
      throw "[ERROR] determinant equal zero";
    } else {
      tmpMatrix = calcComplements();
      tmpMatrix = tmpMatrix.transpose();
      for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row; ++j) {
          tmpMatrix.m_matrix[i][j] = tmpMatrix.m_matrix[i][j] / (double)(d);
        }
      }
    }
  } else {
    throw "[ERROR] matrix is not valid";
  }

  return (tmpMatrix);
}

// -------------------------------------------------------
double **S21Matrix::createArrayDeep2(int rows_, int columns_) {
  double **arr = nullptr;

  if (rows_ > 0 && columns_ > 0) {

    if (!(arr = new double *[rows_]())) {
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows_; i++) {
      if (!(arr[i] = new double[columns_]())) {
        exit(EXIT_FAILURE);
      }
    }
  }
  return (arr);
}

// -------------------------------------------------------

double **S21Matrix::freeArrayDeep2(double **arr_, int rows_) {
  if (arr_) {
    for (int i = 0; i < rows_; i++) {
      if (arr_[i]) {
        delete[] arr_[i];
        arr_[i] = nullptr;
      }
    }
    delete[] arr_;
    arr_ = nullptr;
  }
  return (arr_);
}

// -------------------------------------------------------

std::string S21Matrix::doubleToString(double num_) {
  std::stringstream ss;
  ss.precision(7);
  ss << std::fixed << num_;

  return (ss.str());
}

// -------------------------------------------------------

void S21Matrix::minor(double **B_, int x_, int y_, int N_) {
  int nX = 0;
  int nY = 0;

  for (int i = 0; i < N_; ++i) {
    if (i != x_) {
      nY = 0;

      for (int j = 0; j < N_; ++j) {
        if (j != y_) {
          B_[nX][nY] = m_matrix[i][j];
          ++nY;
        }
      }
      ++nX;
    }
  }
}

// -------------------------------------------------------

void S21Matrix::calcComplements(S21Matrix &matrix_, int N_) {
  double det = 1;
  double **mnr = createArrayDeep2(N_ - 1, N_ - 1);

  for (int j = 0; j < N_; ++j) {
    for (int i = 0; i < N_; ++i) {
      minor(mnr, j, i, N_);
      det = (i + j) % 2 == 0 ? 1 : -1;
      matrix_.m_matrix[j][i] = det * determinant(mnr, N_ - 1);
    }
  }
  freeArrayDeep2(mnr, N_ - 1);
}

// -------------------------------------------------------

void S21Matrix::mult(int m_, int n_, int k_, S21Matrix const &a_,
                     S21Matrix const &b_, S21Matrix &c_) {
  for (int i = 0; i < m_; ++i) {
    for (int j = 0; j < n_; ++j) {
      c_(i, j) = 0;
      for (int k = 0; k < k_; ++k) {
        c_(i, j) += a_(i, k) * b_(k, j);
      }
    }
  }
}

// -------------------------------------------------------

double S21Matrix::determinant(double **arr_, int N_) {
  double res = 0;
  int tmp_j = 0;
  double s = 1;
  double **tmpArr = NULL;

  if (N_ == 1) {
    res = arr_[0][0];
  } else if (N_ == 2) {
    res = arr_[0][0] * arr_[1][1] - (arr_[1][0] * arr_[0][1]);
  } else if (N_ > 2) {
    if (!(tmpArr = new double *[N_ - 1])) {
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N_; i++) {
      tmp_j = 0;
      for (int j = 0; j < N_; j++)
        if (i != j)
          tmpArr[tmp_j++] = arr_[j] + 1;
      res = res + s * arr_[i][0] * determinant(tmpArr, N_ - 1);
      s = -s;
    };
    delete[] tmpArr;
  }

  return (res);
}

// -------------------------------------------------------

void mult(int M_, int N_, int K_, double **A_, double **B_, double **C_) {
  for (int i = 0; i < M_; ++i) {
    for (int j = 0; j < N_; ++j) {
      C_[i][j] = 0;
      for (int k = 0; k < K_; ++k) {
        C_[i][j] += A_[i][k] * B_[k][j];
      }
    }
  }
}

// -------------------------------------------------------

bool S21Matrix::operator==(S21Matrix const &other_) {
  return (eqMatrix(other_));
}

// -------------------------------------------------------

S21Matrix S21Matrix::operator-(S21Matrix const &other_) {
  S21Matrix m(*this);
  m.subMatrix(other_);

  return (m);
}

// -------------------------------------------------------

void S21Matrix::operator-=(S21Matrix const &other_) { this->subMatrix(other_); }

// -------------------------------------------------------

S21Matrix S21Matrix::operator+(S21Matrix const &other_) {
  S21Matrix m(*this);
  m.sumMatrix(other_);

  return (m);
}

// -------------------------------------------------------

void S21Matrix::operator+=(S21Matrix const &other_) { this->sumMatrix(other_); }

// -------------------------------------------------------

S21Matrix S21Matrix::operator*(double num_) {
  S21Matrix m(*this);
  m.mulNumber(num_);

  return (m);
}

// -------------------------------------------------------

void S21Matrix::operator*=(double num_) { this->mulNumber(num_); }

// -------------------------------------------------------

S21Matrix S21Matrix::operator*(S21Matrix const &other_) {
  S21Matrix m(*this);
  m.mulMatrix(other_);

  return (m);
}

// -------------------------------------------------------

void S21Matrix::operator*=(S21Matrix const &other_) { this->mulMatrix(other_); }
