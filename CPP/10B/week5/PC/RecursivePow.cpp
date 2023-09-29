#include <iostream>

// Very simple example of recursion
int pow(int n, int power) {
  int resultval;

  if (power == 0)
    resultval = 1;
  else {
    resultval = n * pow(n, power - 1);
  }

  return resultval;
}

int main() {

  int n = 6;
  cout << n << " squared: " << pow(6) << endl;
  return 0;
}
