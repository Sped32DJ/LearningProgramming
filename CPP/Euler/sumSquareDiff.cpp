#include <cmath>
#include <iostream>
using namespace std;
// FIX  For some reason, both ints, squareSum and sumSquareDiff are both negative int-limit
//
int sumSquareDiff(int n) {
  int sumSquare = 0;
  int squareSum = 0;

  // Note, this loop must be inclusive
  for (int i = 0; i <= n; ++i) {
    sumSquare += pow(i, 2);
  }
  cout << "Sum Square: " << sumSquare << endl;

  for (int i = 0; i <= n; ++i) {
    squareSum += i;
  }
  squareSum = pow(squareSum, 2);
  cout << "Square Sum: " << squareSum << endl;

  return squareSum - sumSquare;
}

int main() {
  int n;
  cout << "Find the Sum Square Difference of: ";
  cin >> n;
  cout << endl;
  cout << "Sum Square Difference of " << n << " is: " << sumSquareDiff(n)
       << endl;
  return 0;
}
