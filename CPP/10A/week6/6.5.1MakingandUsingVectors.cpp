#include <iostream>
#include <vector>
using namespace std;

// Exercise 4
int main() {
  vector<int> dataVector;
  int value;
  int i;

  cin >> value;
  while (value != 0) {
    dataVector.push_back(value);
    cin >> value;
  }

  for (i = 0; i < dataVector.size()-1; ++i) {
    if (dataVector.at(i) > dataVector.back()) { // exclusive, don't include .back()
      cout << "IGNORE" << endl;
    } else {
      cout << dataVector.at(i) << endl;
    }
  }

  return 0;
}

// Exercise 3
/* int main() {
  vector<int> integerVector;
  int value;
  int i;

  cin >> value;
  while (value != -1) {
    integerVector.push_back(value);
    cin >> value;
  }

  // reverse iterate, then only print out values lesser than 0
  // make sure that i = .size() -1 and ; i greater than inclusive 0
  for (i = integerVector.size() - 1; i >= 0; --i) {
    if (integerVector.at(i) < 0) {
      cout << integerVector.at(i) << endl;
    }
  }

  return 0;
} */

// Exercise 2
/* int main() {
  vector<int> inputIntegers;
  int value;
  int i;

  cin >> value;
  while (value != 0) {
    inputIntegers.push_back(value);
    cin >> value;
  }

  int mult = inputIntegers.back();
  inputIntegers.pop_back();
  for (i = 0; i < inputIntegers.size(); ++i) {
    cout << inputIntegers.at(i) * mult << endl;
  }

  return 0;
} */

// Exercise 1
/* int main() {
  vector<int> numberVector;
  int value;
  int i;

  // filling in the vector
  while(cin >> value && value != 0){
      numberVector.push_back(value+3); // Get the value, and add 3
  }

  for (i = 0; i < numberVector.size(); ++i) {
    cout << numberVector.at(i) << endl;
  }

  return 0;
} */
