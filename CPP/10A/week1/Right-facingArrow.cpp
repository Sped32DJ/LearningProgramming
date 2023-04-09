#include <iostream>
using namespace std;

int main() {
  int baseDigit, headDigit;
  string space = "     ";
  cin >> baseDigit >> headDigit;

  // Print the top two lines
  cout << space << headDigit << endl;
  cout << space << headDigit << headDigit << endl;

  // Print the middle three lines
  for (int i = 0; i < 5; i++) {
    cout << baseDigit;
  }
  for (int j = 0; j < 3; j++) { // 3 headDigit
    cout << headDigit;
  }
  cout << endl;

  for (int i = 0; i < 5; i++) {
    cout << baseDigit;
  }
  for (int j = 0; j < 4; j++) { // 4 headDigit
    cout << headDigit;
  }
  cout << endl;

  for (int i = 0; i < 5; i++) {
    cout << baseDigit;
  }
  for (int j = 0; j < 3; j++) { // 3 headDigit
    cout << headDigit;
  }
  cout << endl;

  // Print the bottom two lines
  cout << space << headDigit << headDigit << endl;
  cout << space << headDigit << endl;

  return 0;
}
