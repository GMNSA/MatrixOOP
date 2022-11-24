#include "test_matrix_oop.h"
#include <gtest/gtest.h>
#include <string>

#include "s21_matrix_oop.h"

TEST_F(TestMatrixOOP, Foo1) {}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, IsValid) {
  S21Matrix matrix;

  ASSERT_EQ(matrix.isValid(), 0);

  matrix.resize(1, 4);
  ASSERT_EQ(matrix.isValid(), 1);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, SumMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2;

  matrix1(0, 0) = 12;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = 0;

  try {
    matrix1.sumMatrix(matrix2);
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] row, col is not valid", msg);
  }

  matrix2.resize(2, 3);

  try {
    matrix1.sumMatrix(matrix2);
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] row and col is not equal", msg);
  }

  matrix2.resize(2, 2);
  matrix2(0, 0) = -4;
  matrix2(0, 1) = -3;
  matrix2(1, 0) = 15;
  matrix2(1, 1) = 7;

  matrix1.sumMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 8);
  ASSERT_EQ(matrix1(0, 1), -4);
  ASSERT_EQ(matrix1(1, 0), 10);
  ASSERT_EQ(matrix1(1, 1), 7);

  // ***********

  matrix1(0, 0) = 122;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = 0;

  matrix2(0, 0) = -44;
  matrix2(0, 1) = -3;
  matrix2(1, 0) = 150;
  matrix2(1, 1) = 7;

  matrix1.sumMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 78);
  ASSERT_EQ(matrix1(0, 1), -4);
  ASSERT_EQ(matrix1(1, 0), 145);
  ASSERT_EQ(matrix1(1, 1), 7);

  // ***********

  matrix1(0, 0) = 1;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = -8;

  matrix2(0, 0) = -4399488;
  matrix2(0, 1) = -3004;
  matrix2(1, 0) = 150577;
  matrix2(1, 1) = -7;

  matrix1.sumMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), -4399487);
  ASSERT_EQ(matrix1(0, 1), -3005);
  ASSERT_EQ(matrix1(1, 0), 150572);
  ASSERT_EQ(matrix1(1, 1), -15);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, EqualMatrix) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  S21Matrix m3(3, 2);

  m1(0, 0) = 1;
  m2(0, 1) = 1;
  m3(0, 0) = 1;

  EXPECT_EQ(m1 == m2, 0);

  m2(0, 1) = 0;
  m2(0, 0) = 1;

  ASSERT_EQ(m1 == m2, 1);
  ASSERT_EQ(m3 == m1, 0);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, SubMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2;

  matrix1(0, 0) = 12;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = 0;

  try {
    matrix1.sumMatrix(matrix2);
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] row, col is not valid", msg);
  }

  matrix2.resize(2, 3);

  try {
    matrix1.sumMatrix(matrix2);
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] row and col is not equal", msg);
  }

  // ***********

  matrix2.resize(2, 2);
  matrix2(0, 0) = -4;
  matrix2(0, 1) = -3;
  matrix2(1, 0) = 15;
  matrix2(1, 1) = 7;

  matrix1.subMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 16);
  ASSERT_EQ(matrix1(0, 1), 2);
  ASSERT_EQ(matrix1(1, 0), -20);
  ASSERT_EQ(matrix1(1, 1), -7);

  // ***********

  matrix1(0, 0) = 122;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = 0;

  matrix2(0, 0) = -44;
  matrix2(0, 1) = -3;
  matrix2(1, 0) = 150;
  matrix2(1, 1) = 7;

  matrix1.subMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 166);
  ASSERT_EQ(matrix1(0, 1), 2);
  ASSERT_EQ(matrix1(1, 0), -155);
  ASSERT_EQ(matrix1(1, 1), -7);

  // ***********

  matrix1(0, 0) = 1;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = -8;

  matrix2(0, 0) = -4399488;
  matrix2(0, 1) = -3004;
  matrix2(1, 0) = 150577;
  matrix2(1, 1) = -7;

  matrix1.subMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 4399489);
  ASSERT_EQ(matrix1(0, 1), 3003);
  ASSERT_EQ(matrix1(1, 0), -150582);
  ASSERT_EQ(matrix1(1, 1), -1);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, MulNum) {
  S21Matrix matrix(3, 3);
  double num = 2;

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 2;
  matrix(2, 1) = 3;
  matrix(2, 2) = 4;

  matrix.mulNumber(num);

  ASSERT_EQ(matrix(0, 0), 2);
  ASSERT_EQ(matrix(0, 1), 4);
  ASSERT_EQ(matrix(0, 2), 6);
  ASSERT_EQ(matrix(1, 0), 0);
  ASSERT_EQ(matrix(1, 1), 8);
  ASSERT_EQ(matrix(1, 2), 4);
  ASSERT_EQ(matrix(2, 0), 4);
  ASSERT_EQ(matrix(2, 1), 6);
  ASSERT_EQ(matrix(2, 2), 8);

  // ***********

  num = 0.8;

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 2;
  matrix(2, 1) = 3;
  matrix(2, 2) = 4;

  matrix.mulNumber(num);

  ASSERT_EQ(matrix.doubleToString(matrix(0, 0)), "0.8000000");
  ASSERT_EQ(matrix.doubleToString(matrix(0, 1)), "1.6000000");
  ASSERT_EQ(matrix.doubleToString(matrix(0, 2)), "2.4000000");
  ASSERT_EQ(matrix.doubleToString(matrix(1, 0)), "0.0000000");
  ASSERT_EQ(matrix.doubleToString(matrix(1, 1)), "3.2000000");
  ASSERT_EQ(matrix.doubleToString(matrix(1, 2)), "1.6000000");
  ASSERT_EQ(matrix.doubleToString(matrix(2, 0)), "1.6000000");
  ASSERT_EQ(matrix.doubleToString(matrix(2, 1)), "2.4000000");
  ASSERT_EQ(matrix.doubleToString(matrix(2, 2)), "3.2000000");

  // ***********

  num = 1.8;

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 2;
  matrix(2, 1) = 3;
  matrix(2, 2) = 4;

  matrix.mulNumber(num);

  ASSERT_EQ(matrix.doubleToString(matrix(0, 0)), "1.8000000");
  ASSERT_EQ(matrix.doubleToString(matrix(0, 1)), "3.6000000");
  ASSERT_EQ(matrix.doubleToString(matrix(0, 2)), "5.4000000");
  ASSERT_EQ(matrix.doubleToString(matrix(1, 0)), "0.0000000");
  ASSERT_EQ(matrix.doubleToString(matrix(1, 1)), "7.2000000");
  ASSERT_EQ(matrix.doubleToString(matrix(1, 2)), "3.6000000");
  ASSERT_EQ(matrix.doubleToString(matrix(2, 0)), "3.6000000");
  ASSERT_EQ(matrix.doubleToString(matrix(2, 1)), "5.4000000");
  ASSERT_EQ(matrix.doubleToString(matrix(2, 2)), "7.2000000");
  ASSERT_NE(matrix.doubleToString(matrix(2, 2)), "7.2000003");

  // ***********
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, MulMatrix) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(5, 4);

  try {
    matrix1.mulMatrix(matrix2);
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] matrix 1 (cols) != matrix 2 (rows)", msg);
  }

  matrix1.resize(3, 2);
  matrix2.resize(2, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 3;
  matrix1(2, 1) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = -1;
  matrix2(0, 2) = 1;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 3;
  matrix2(1, 2) = 4;

  matrix1.mulMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 9);
  ASSERT_EQ(matrix1(0, 1), 11);
  ASSERT_EQ(matrix1(0, 2), 17);
  ASSERT_EQ(matrix1(1, 0), 12);
  ASSERT_EQ(matrix1(1, 1), 13);
  ASSERT_EQ(matrix1(1, 2), 22);
  ASSERT_EQ(matrix1(2, 0), 15);
  ASSERT_EQ(matrix1(2, 1), 15);
  ASSERT_EQ(matrix1(2, 2), 27);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, Transpose) {
  S21Matrix matrix(3, 2);

  matrix(0, 0) = 1;
  matrix(0, 1) = 4;
  matrix(1, 0) = 2;
  matrix(1, 1) = 5;
  matrix(2, 0) = 3;
  matrix(2, 1) = 6;

  auto matrix2 = matrix.transpose();

  ASSERT_EQ(matrix2(0, 0), 1);
  ASSERT_EQ(matrix2(0, 1), 2);
  ASSERT_EQ(matrix2(0, 2), 3);
  ASSERT_EQ(matrix2(1, 0), 4);
  ASSERT_EQ(matrix2(1, 1), 5);
  ASSERT_EQ(matrix2(1, 2), 6);

  /* *****  ***** */

  matrix.resize(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 4;
  matrix(0, 2) = 7;
  matrix(1, 0) = 2;
  matrix(1, 1) = 5;
  matrix(1, 2) = 8;
  matrix(2, 0) = 3;
  matrix(2, 1) = 6;
  matrix(2, 2) = 9;

  matrix2 = matrix.transpose();

  ASSERT_EQ(matrix2(0, 0), 1);
  ASSERT_EQ(matrix2(0, 1), 2);
  ASSERT_EQ(matrix2(0, 2), 3);
  ASSERT_EQ(matrix2(1, 0), 4);
  ASSERT_EQ(matrix2(1, 1), 5);
  ASSERT_EQ(matrix2(1, 2), 6);
  ASSERT_EQ(matrix2(2, 0), 7);
  ASSERT_EQ(matrix2(2, 1), 8);
  ASSERT_EQ(matrix2(2, 2), 9);

  /* *****  ***** */

  matrix.resize(1, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 4;
  matrix(0, 2) = 2;

  matrix2 = matrix.transpose();

  ASSERT_EQ(matrix2(0, 0), 1);
  ASSERT_EQ(matrix2(1, 0), 4);
  ASSERT_EQ(matrix2(2, 0), 2);

  /* *****  ***** */

  matrix.resize(1, 1);

  matrix(0, 0) = 1;

  matrix2 = matrix.transpose();

  S21Matrix mat3(S21Matrix(3, 4));

  ASSERT_EQ(matrix2(0, 0), 1);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, Determinant) {
  S21Matrix matrix(3, 2);
  double num = 0;

  try {
    num = matrix.determinant();
    ASSERT_EQ(num, 0);

    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] matrix is not valid", msg);
  }

  /* *****  ***** */

  matrix.resize(2, 3);

  try {
    num = matrix.determinant();
    ASSERT_EQ(num, 0);

    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] matrix is not valid", msg);
  }

  /* *****  ***** */

  matrix.resize(1, 1);

  matrix(0, 0) = 4;
  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, 4);

  /* *****  ***** */

  matrix(0, 0) = -8.4;
  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, -8.4);

  /* *****  ***** */

  matrix.resize(2, 2);

  matrix(0, 0) = 4.9;
  matrix(0, 1) = -3.394;
  matrix(1, 0) = 1;
  matrix(1, 1) = 6;

  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, 32.794);

  /* *****  ***** */

  matrix.resize(2, 2);

  matrix(0, 0) = 4;
  matrix(0, 1) = 3;
  matrix(1, 0) = 1;
  matrix(1, 1) = 6;

  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, 21);

  /* *****  ***** */

  matrix.resize(3, 3);

  matrix(0, 0) = 4;
  matrix(0, 1) = 3;
  matrix(0, 2) = 5;
  matrix(1, 0) = 1;
  matrix(1, 1) = 6;
  matrix(1, 2) = 7;
  matrix(2, 0) = 12;
  matrix(2, 1) = -5;
  matrix(2, 2) = -8;

  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, -161);

  /* *****  ***** */

  matrix.resize(4, 4);

  matrix(0, 0) = 4;
  matrix(0, 1) = 3;
  matrix(0, 2) = 5;
  matrix(0, 3) = 4;
  matrix(1, 0) = 1;
  matrix(1, 1) = 6;
  matrix(1, 2) = 7;
  matrix(1, 3) = 48.94;
  matrix(2, 0) = 12;
  matrix(2, 1) = -5;
  matrix(2, 2) = -8;
  matrix(2, 3) = 47.88;
  matrix(3, 0) = 5;
  matrix(3, 1) = 24;
  matrix(3, 2) = 67.3267;
  matrix(3, 3) = 11.99;

  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, -105091.083804);

  /* *****  ***** */

  matrix.resize(4, 4);

  matrix(0, 0) = 4;
  matrix(0, 1) = 3;
  matrix(0, 2) = 5;
  matrix(0, 3) = 4;
  matrix(1, 0) = 1;
  matrix(1, 1) = 6;
  matrix(1, 2) = 7;
  matrix(1, 3) = 48;
  matrix(2, 0) = 12;
  matrix(2, 1) = -5;
  matrix(2, 2) = -8;
  matrix(2, 3) = 47;
  matrix(3, 0) = 5;
  matrix(3, 1) = 24;
  matrix(3, 2) = 67;
  matrix(3, 3) = 11;

  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, -101649);

  /* *****  ***** */

  matrix.resize(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;

  num = 0;
  num = matrix.determinant();

  ASSERT_FLOAT_EQ(num, -40);

  /* *****  ***** */
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, CalcComplements) {
  S21Matrix matrix(3, 2);
  S21Matrix matrix2;

  try {
    matrix2 = matrix.calcComplements();
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] Matrix is not square", msg);
  }

  /* *****  ***** */

  matrix.resize(1, 1);

  try {
    matrix2 = matrix.calcComplements();
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] Matrix is not square", msg);
  }

  /* *****  ***** */

  matrix.resize(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;

  matrix2 = matrix.calcComplements();

  ASSERT_FLOAT_EQ(matrix2(0, 0), 0);
  ASSERT_FLOAT_EQ(matrix2(0, 1), 10);
  ASSERT_FLOAT_EQ(matrix2(0, 2), -20);
  ASSERT_FLOAT_EQ(matrix2(1, 0), 4);
  ASSERT_FLOAT_EQ(matrix2(1, 1), -14);
  ASSERT_FLOAT_EQ(matrix2(1, 2), 8);
  ASSERT_FLOAT_EQ(matrix2(2, 0), -8);
  ASSERT_FLOAT_EQ(matrix2(2, 1), -2);
  ASSERT_FLOAT_EQ(matrix2(2, 2), 4);

  /* *****  ***** */

  matrix.resize(2, 2);

  matrix(0, 0) = 14.94;
  matrix(0, 1) = -2;
  matrix(1, 0) = -894.399;
  matrix(1, 1) = 4.9;

  matrix2 = matrix.calcComplements();

  ASSERT_FLOAT_EQ(matrix2(0, 0), 4.9);
  ASSERT_FLOAT_EQ(matrix2(0, 1), 894.399);
  ASSERT_FLOAT_EQ(matrix2(1, 0), 2);
  ASSERT_FLOAT_EQ(matrix2(1, 1), 14.94);

  /* *****  ***** */

  matrix.resize(2, 2);

  matrix(0, 0) = -14.94;
  matrix(0, 1) = -28.95;
  matrix(1, 0) = 894.399;
  matrix(1, 1) = 41.99;

  matrix2 = matrix.calcComplements();

  ASSERT_FLOAT_EQ(matrix2(0, 0), 41.99);
  ASSERT_FLOAT_EQ(matrix2(0, 1), -894.399);
  ASSERT_FLOAT_EQ(matrix2(1, 0), 28.95);
  ASSERT_FLOAT_EQ(matrix2(1, 1), -14.94);

  /* *****  ***** */

  matrix.resize(4, 4);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(0, 3) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = -4;
  matrix(1, 2) = 2;
  matrix(1, 3) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2.3;
  matrix(2, 2) = 1;
  matrix(2, 3) = 1.9;
  matrix(3, 0) = 5;
  matrix(3, 1) = -3;
  matrix(3, 2) = 8;
  matrix(3, 3) = 3.2;

  matrix2 = matrix.calcComplements();

  ASSERT_FLOAT_EQ(matrix2(0, 0), 20.52);
  ASSERT_FLOAT_EQ(matrix2(0, 1), -57);
  ASSERT_FLOAT_EQ(matrix2(0, 2), 19);
  ASSERT_FLOAT_EQ(matrix2(0, 3), -133);
  ASSERT_FLOAT_EQ(matrix2(1, 0), 65.22);
  ASSERT_FLOAT_EQ(matrix2(1, 1), 73.5);
  ASSERT_FLOAT_EQ(matrix2(1, 2), 25.16);
  ASSERT_FLOAT_EQ(matrix2(1, 3), -95.9);
  ASSERT_FLOAT_EQ(matrix2(2, 0), -76.8);
  ASSERT_FLOAT_EQ(matrix2(2, 1), 9.6);
  ASSERT_FLOAT_EQ(matrix2(2, 2), 73.2);
  ASSERT_FLOAT_EQ(matrix2(2, 3), -54);
  ASSERT_FLOAT_EQ(matrix2(3, 0), -14.4);
  ASSERT_FLOAT_EQ(matrix2(3, 1), 1.8);
  ASSERT_FLOAT_EQ(matrix2(3, 2), -77);
  ASSERT_FLOAT_EQ(matrix2(3, 3), 80.6);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, InverseMatrix) {
  S21Matrix matrix(2, 3);
  S21Matrix res(2, 2);
  S21Matrix c;

  try {
    matrix.inverseMatrix();
    FAIL();
  } catch (char const *msg) {
    ASSERT_STREQ("[ERROR] matrix is not valid", msg);
  }

  matrix.resize(2, 2);

  matrix(0, 0) = 2.8;
  matrix(0, 1) = 2;
  matrix(1, 0) = -4.8;
  matrix(1, 1) = 42;

  c = matrix.inverseMatrix();

  res(0, 0) = 0.3301887;
  res(0, 1) = -0.0157233;
  res(1, 0) = 0.0377358;
  res(1, 1) = 0.0220126;

  ASSERT_EQ(c == res, 1);

  /* *****  ***** */

  matrix.resize(3, 3);
  res.resize(3, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  c = matrix.inverseMatrix();

  res(0, 0) = 1;
  res(0, 1) = -1;
  res(0, 2) = 1;
  res(1, 0) = -38;
  res(1, 1) = 41;
  res(1, 2) = -34;
  res(2, 0) = 27;
  res(2, 1) = -29;
  res(2, 2) = 24;

  ASSERT_EQ(c == res, 1);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, SubOperator) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 10;
  m1(0, 1) = 10;
  m1(1, 0) = 10;
  m1(1, 1) = 10;

  m2(0, 0) = 3;
  m2(0, 1) = 4;
  m2(1, 0) = 5;
  m2(1, 1) = 6;

  S21Matrix res = m1 - m2;

  ASSERT_EQ(res(0, 0), 7);
  ASSERT_EQ(res(0, 1), 6);
  ASSERT_EQ(res(1, 0), 5);
  ASSERT_EQ(res(1, 1), 4);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, SubEqual) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 122;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = 0;

  matrix2(0, 0) = -44;
  matrix2(0, 1) = -3;
  matrix2(1, 0) = 150;
  matrix2(1, 1) = 7;

  matrix1 -= matrix2;

  ASSERT_EQ(matrix1(0, 0), 166);
  ASSERT_EQ(matrix1(0, 1), 2);
  ASSERT_EQ(matrix1(1, 0), -155);
  ASSERT_EQ(matrix1(1, 1), -7);

  /* *****  ***** */

  matrix1(0, 0) = 1;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = -8;

  matrix2(0, 0) = -4399488;
  matrix2(0, 1) = -3004;
  matrix2(1, 0) = 150577;
  matrix2(1, 1) = -7;

  matrix1 -= matrix2;

  ASSERT_EQ(matrix1(0, 0), 4399489);
  ASSERT_EQ(matrix1(0, 1), 3003);
  ASSERT_EQ(matrix1(1, 0), -150582);
  ASSERT_EQ(matrix1(1, 1), -1);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, SumOperator) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 10;
  m1(0, 1) = 10;
  m1(1, 0) = 10;
  m1(1, 1) = 10;

  m2(0, 0) = 3;
  m2(0, 1) = 4;
  m2(1, 0) = 5;
  m2(1, 1) = 6;

  S21Matrix res = m1 + m2;

  ASSERT_EQ(res(0, 0), 13);
  ASSERT_EQ(res(0, 1), 14);
  ASSERT_EQ(res(1, 0), 15);
  ASSERT_EQ(res(1, 1), 16);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, SumEqual) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 122;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = 0;

  matrix2(0, 0) = -44;
  matrix2(0, 1) = -3;
  matrix2(1, 0) = 150;
  matrix2(1, 1) = 7;

  matrix1 += matrix2;

  ASSERT_EQ(matrix1(0, 0), 78);
  ASSERT_EQ(matrix1(0, 1), -4);
  ASSERT_EQ(matrix1(1, 0), 145);
  ASSERT_EQ(matrix1(1, 1), 7);

  // ***********

  matrix1(0, 0) = 1;
  matrix1(0, 1) = -1;
  matrix1(1, 0) = -5;
  matrix1(1, 1) = -8;

  matrix2(0, 0) = -4399488;
  matrix2(0, 1) = -3004;
  matrix2(1, 0) = 150577;
  matrix2(1, 1) = -7;

  matrix1 += matrix2;

  ASSERT_EQ(matrix1(0, 0), -4399487);
  ASSERT_EQ(matrix1(0, 1), -3005);
  ASSERT_EQ(matrix1(1, 0), 150572);
  ASSERT_EQ(matrix1(1, 1), -15);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, MulOperatorNum) {

  S21Matrix matrix(3, 3);
  S21Matrix matrix2;
  double num = 2;

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 2;
  matrix(2, 1) = 3;
  matrix(2, 2) = 4;

  matrix2 = matrix * num;

  ASSERT_EQ(matrix2(0, 0), 2);
  ASSERT_EQ(matrix2(0, 1), 4);
  ASSERT_EQ(matrix2(0, 2), 6);
  ASSERT_EQ(matrix2(1, 0), 0);
  ASSERT_EQ(matrix2(1, 1), 8);
  ASSERT_EQ(matrix2(1, 2), 4);
  ASSERT_EQ(matrix2(2, 0), 4);
  ASSERT_EQ(matrix2(2, 1), 6);
  ASSERT_EQ(matrix2(2, 2), 8);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, MulOperatorEqualNum) {
  S21Matrix matrix(3, 3);
  double num = 2;

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 2;
  matrix(2, 1) = 3;
  matrix(2, 2) = 4;

  matrix *= num;

  ASSERT_EQ(matrix(0, 0), 2);
  ASSERT_EQ(matrix(0, 1), 4);
  ASSERT_EQ(matrix(0, 2), 6);
  ASSERT_EQ(matrix(1, 0), 0);
  ASSERT_EQ(matrix(1, 1), 8);
  ASSERT_EQ(matrix(1, 2), 4);
  ASSERT_EQ(matrix(2, 0), 4);
  ASSERT_EQ(matrix(2, 1), 6);
  ASSERT_EQ(matrix(2, 2), 8);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, MulOperatorMatrix) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 3);
  S21Matrix res;

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 3;
  matrix1(2, 1) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = -1;
  matrix2(0, 2) = 1;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 3;
  matrix2(1, 2) = 4;

  res = matrix1 * matrix2;

  ASSERT_EQ(res(0, 0), 9);
  ASSERT_EQ(res(0, 1), 11);
  ASSERT_EQ(res(0, 2), 17);
  ASSERT_EQ(res(1, 0), 12);
  ASSERT_EQ(res(1, 1), 13);
  ASSERT_EQ(res(1, 2), 22);
  ASSERT_EQ(res(2, 0), 15);
  ASSERT_EQ(res(2, 1), 15);
  ASSERT_EQ(res(2, 2), 27);
}

// -------------------------------------------------------

TEST_F(TestMatrixOOP, MulOperatorMatrixEqual) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 5;
  matrix1(2, 0) = 3;
  matrix1(2, 1) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = -1;
  matrix2(0, 2) = 1;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 3;
  matrix2(1, 2) = 4;

  matrix1 *= matrix2;

  ASSERT_EQ(matrix1(0, 0), 9);
  ASSERT_EQ(matrix1(0, 1), 11);
  ASSERT_EQ(matrix1(0, 2), 17);
  ASSERT_EQ(matrix1(1, 0), 12);
  ASSERT_EQ(matrix1(1, 1), 13);
  ASSERT_EQ(matrix1(1, 2), 22);
  ASSERT_EQ(matrix1(2, 0), 15);
  ASSERT_EQ(matrix1(2, 1), 15);
  ASSERT_EQ(matrix1(2, 2), 27);
}

// -------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
