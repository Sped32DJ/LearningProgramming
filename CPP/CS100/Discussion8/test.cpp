#include "fizzString.cpp"
#include "gtest/gtest.h"

TEST(fizzStringTest, Positive) {
  FizzString obj;
  EXPECT_EQ("Fizz", obj.fizzString("fig"));
  EXPECT_EQ("Buzz", obj.fizzString("dib"));
  EXPECT_EQ("FizzBuzz", obj.fizzString("fib"));
}

TEST(fizzStringTest, Negative) {
  FizzString obj;
  ;
}
