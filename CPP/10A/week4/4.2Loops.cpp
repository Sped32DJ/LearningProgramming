#include <iostream>
using namespace std;

int main() {
  int userIn;
  int outputVal;

  outputVal = 0;
  cin >> userIn;

  while (userIn >= 0) {
    if (userIn % 5 == 0) {
      cout << "hit";
      ++outputVal;
    } else {
      cout << "miss";
    }
    cout << endl;
    cin >> userIn;
  }

  cout << "Output value is " << outputVal << endl;

  return 0;
}
