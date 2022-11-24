#ifndef TEST_MATRIX_OOP_H
#define TEST_MATRIX_OOP_H

#include <gtest/gtest.h>

class TestMatrixOOP : public ::testing::Test {
public:
  TestMatrixOOP() {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~TestMatrixOOP() {
    // cleanup any pending stuff, but no exceptions allowed
  }

private:
  // put in any custom data members that you need
};

#endif // TEST_MATRIX_OOP_H
