#include <iostream>
using namespace std;

int main() {
  int currentInput;
  int previousInput;

  cin >> previousInput;
  cout << previousInput << " is in a non-increasing sequence." << endl;
  currentInput = previousInput;

  while (cin >> currentInput) {
    if (currentInput <= previousInput) {
      cout << currentInput << " is in a non-increasing sequence." << endl;
    } else {
      cout << currentInput << " breaks the sequence." << endl;
      break;
    }
    previousInput = currentInput;
  }

  return 0;
}
