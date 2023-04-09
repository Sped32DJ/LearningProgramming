#include <iostream>
using namespace std;

int main() {
  int baseDigit;
  int headDigit;
  cin >> baseDigit;
  cin >> headDigit;

  cout << "     " << headDigit << endl;

  cout << "     " << headDigit << headDigit << endl;

  cout << baseDigit << baseDigit << baseDigit << baseDigit << baseDigit
       << headDigit << headDigit << headDigit << endl;

  cout << baseDigit << baseDigit << baseDigit << baseDigit << baseDigit
       << headDigit << headDigit << headDigit << headDigit << endl;
  cout << baseDigit << baseDigit << baseDigit << baseDigit << baseDigit
       << headDigit << headDigit << headDigit << endl;

  cout << "     " << headDigit << headDigit << endl;

  cout << "     " << headDigit << endl;

  return 0;
}
