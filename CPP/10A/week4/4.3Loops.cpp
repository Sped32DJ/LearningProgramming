#include <iostream>
using namespace std;

// DOES NOT FUNCTION CORRECTLY
int main() {
  int currentInput;
  int previousInput;

  cin >> previousInput;
  cout << previousInput << " is in a non-increasing sequence." << endl;
  currentInput = previousInput;

  while (previousInput <= currentInput) {
    cin >> currentInput;
    cout << currentInput << " is in a non-increasing sequence." << endl;
    previousInput = currentInput;
  }

  cin >> currentInput;
  cout << currentInput << " breaks the sequence.\n";

  return 0;
}
