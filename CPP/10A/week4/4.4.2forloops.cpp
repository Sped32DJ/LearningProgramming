#include <iostream>
using namespace std;

int main() {
  int numVals;
  int in, i;

  cin >> numVals;

  for (i = 0; i < 1; ++i) {
    for (i = 1; i < numVals; ++i) {
      cin >> in;
      cout << in << ": ";
    }
    cin >> in;
    cout << in;
  }
  cout << endl;

  return 0;
}

/* int main() { // Exercise 2
  int inputCount;
  int in, i;

  cin >> inputCount;
  for (i = 0; i < inputCount; ++i) {
    cin >> in;
    cout << '[' << in << ']';
  }
  cout << endl;

  return 0;
} */

/* int main() { // Exercise 1
  int numInput;
  int value;
  int i;

  cin >> numInput;

  for (i = 0; i < numInput; ++i) {
    cin >> value;
    cout << "position: " << value << endl;
  }

  return 0;
} */
