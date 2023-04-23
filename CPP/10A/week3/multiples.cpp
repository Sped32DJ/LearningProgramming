#include <iostream>
using namespace std;

int main() {

  int uno, dos, tres, cat;
  cin >> uno >> dos >> tres;

  cat = dos * tres;

  /* if (uno % dos == 0 || uno % tres == 0) {
    if (uno % dos == 0) {
      cout << uno << " is a multiple of " << dos << ".";
    } else if (uno % tres == 0) {
      cout << uno << " is a multiple of " << tres << ".";
    }
  } else {
//    cout << uno << " is not a multiple of 5, 7, or 35";
    cout << uno << " is not a multiple of " << dos << ", " << tres;
  }
  cout << endl; */

  if (uno % dos == 0) {
    cout << uno << " is a multiple of " << dos << '.' << endl;
  }
  if (uno % tres == 0) {
    cout << uno << " is a multiple of " << tres << '.' << endl;
  }
  if (uno % cat == 0) {
    cout << uno << " is a multiple of " << cat << '.' << endl;
  }

  // Error, no multiples
  if (uno % dos != 0 && uno % tres != 0) {
    cout << uno << " is not a multiple of " << dos << ", " << tres << ", or "
         << cat << '.' << endl;
  }
  return 0;
}
