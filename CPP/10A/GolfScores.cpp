#include <iostream>
#include <string>
using namespace std;

int main() {
  int par;
  int strokes;
  string name;

  cin >> strokes >> par;

  /* if (strokes > (par - 2)) {
    cout << "Birdie";
  } else if (strokes > (par - 1)) {
    cout << "Eagle";
  } else if (strokes == par) {
    cout << "Par";
  } else {
    cout << "Bogey";
  }  */
  if (strokes > par - 1 && (strokes > 1)) {
    if (strokes == par) {
      cout << "Par";
    } else if (strokes - 1 == par) {
      cout << "Birdie";
    } else if (strokes - 2 == par) {
      cout << "Eagle";
    } else if (strokes + 1 == par) {
      cout << "Bogey";
    }
  } else if (strokes + 1 == par && (strokes > 1)) {
    cout << "Bogey";
  } else {
    cout << "Error";
  }
  cout << endl;
  /* Type your code here */

  return 0;
}
