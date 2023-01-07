#include <iostream>
using namespace std;

int power(int baseNum, int powNum) {
  int result = 1;

  for (int i = 0; i < powNum; i++) {
    result = result * baseNum;
  }

  return result; // Returns result of functions (garbage collection 101)
}

int main() {

  int base;
  int pwr;
  cout << "Base: ";
  cin >> base;
  cout << "To the power of: ";
  cin >> pwr;
  cout << power(base, pwr) << endl;

  return 0;
}
