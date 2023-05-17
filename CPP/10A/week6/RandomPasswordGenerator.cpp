#include <cstdlib>
#include <iostream>
using namespace std;

int main() {

  int numDigits;
  cin >> numDigits;
  srand(44);

  // validating inputs, range 0-9
  if (numDigits <= 0 || numDigits > 9) {
    cout << "Not valid to generate a password." << endl;
  } else {

    int password = 0;
    for (int i = 0; i < numDigits; ++i) {
      int digit = rand() % 10;
      password = password * 10 + digit;
    }
    cout << "Your password should be " << password << '.' << endl;
  }

  return 0;
}
