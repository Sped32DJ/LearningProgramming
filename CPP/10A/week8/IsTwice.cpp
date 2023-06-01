#include <iostream>
#include <vector>
using namespace std;

/* Your code goes here */
bool IsTwice(vector<int> a, vector<int> b) {
  if (a.at(0) == b.at(0) * 2 && a.at(1) == b.at(1) * 2){
    return true;
  }
  return false;
}

int main() {
  int i;
  vector<int> inputVector1;
  vector<int> inputVector2;
  int size;
  int input;
  bool checkProperty;

  cin >> size;
  for (i = 0; i < size; ++i) {
    cin >> input;
    inputVector1.push_back(input);
  }

  cin >> size;
  for (i = 0; i < size; ++i) {
    cin >> input;
    inputVector2.push_back(input);
  }

  checkProperty = IsTwice(inputVector1, inputVector2);

  if (checkProperty) {
    cout << "True, the first vector is twice the second vector." << endl;
  } else {
    cout << "False, the first vector is not twice the second vector." << endl;
  }

  return 0;
}
