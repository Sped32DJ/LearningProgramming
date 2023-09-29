#include <iostream>

// It goes nothing like this
double squirt(int num, int n) {
  int val;

  if (n == 0)
    return 1;
  else
    val = n / squirt(num, n - 1);
  return val;
}
