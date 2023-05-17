#include <iostream>
using namespace std;

bool CheckVals() {
  int val;
  while (val != 0) {
    cin >> val;
    if (val >= 100 && val <= 200) {
      return false;
    }
  }
  return true;
}

int main() {
  bool allAllowed;

  allAllowed = CheckVals();
  if (allAllowed) {
    cout << "All allowed values" << endl;
  } else {
    cout << "Unallowed value(s)" << endl;
  }

  return 0;
}
