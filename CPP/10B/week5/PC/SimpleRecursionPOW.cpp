#include <iostream>
using namespace std;

int RaiseToPower(int baseVal, int exponentVal) {
  int resultVal;

  if (exponentVal == 0) {
    resultVal = 1;
  } else {
    resultVal = baseVal * RaiseToPower(baseVal, exponentVal - 1);
  }

  return resultVal;
}

int main() {
  int userBase;
  int userExponent;

  cin >> userBase;
  cin >> userExponent;
  cout << userBase << "^" << userExponent << " = "
       << RaiseToPower(userBase, userExponent) << endl;

  return 0;
}
