#include <cmath>
#include <iostream>
using namespace std;

int main() {
  int i, uno, dos, tres;

  // num = iteratinos
  cin >> uno >> dos >> tres;

  /* num = fabs(dos - uno); */

  if (tres == 0) { // case 0
    if (dos - 1 != uno) { // if statement is boof
      for (i = uno + 1; i < dos; ++i) {
        cout << i << ' ';
        /* cout << "test"; */
      }
    } else {
      cout << "No output.";
    }
  } else if (tres == 1) { // case 1
    if (dos > uno) {
      for (i = uno; i < dos + 1; ++i) {
        cout << i << ' ';
      }
    } else {
      cout << "No output.";
    }
  } else {
    cout << "No output";
  }
  cout << endl;

  return 0;
}
