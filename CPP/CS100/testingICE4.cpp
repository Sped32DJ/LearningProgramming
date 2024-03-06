#include <cmath>

TEST(testingArea, positiveValues) {
  Circle circ;
  circ.radius(2);
  EXPECT_DOUBLE_EQ(circ.area(), 3.14 * (2 * 2))
}

// Checks if pi is at least 3.14
TEST(testingArea, correctValueOfPi) {
  Circle circ;
  circ.radius(1);             // pi * r ^2 (r=1)
  int pi = circ.area() * 100; // Should be 314 (3.14*10^2)
  EXPECT_EQ(pi, 314);
}

TEST(testingArea, testingPerimeter) {
  Circle circ;
  circ.radius(2);
  EXPECT_DOUBLE_EQ(circ.area(), 4 * M_PI)
}

// Test may fail, depending on how function is written
TEST(testingArea, negativeValuesCrashTest) {
  Circle circ;
  // should crash from inputting negative values
  // Or throw error
  EXPECT_DEATH(circ.radius(-2));
}

TEST(testingArea, negativeValThrow) {
  Circle circ;
  // if any error is throw, test pass
  EXPECT_ANY_THROW(circ.radius(-2));
}
