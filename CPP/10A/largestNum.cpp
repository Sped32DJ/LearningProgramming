#include <iostream>
using namespace std;

int main() {

  int uno, dos, tres;
  cin >> uno >> dos >> tres;

  if (uno > dos && uno > tres) {
    cout << uno << endl;
  }
  if (dos > uno && dos > tres) {
    cout << dos << endl;
  }
  if (tres > uno && tres > uno) {
    cout << tres << endl;
  }

  // check how many times it went through
  if (uno == dos) {
    if (uno == tres) {
      cout << '2' << endl;
    }
  } else if (uno == dos) {
    cout << '1' << endl;
  }

  if (dos == uno) {
    cout << '2' << endl;
  } else if (dos == tres) {
    cout << '1' << endl;
  }

  if (tres == uno) {
    cout << '2' << endl;
  } else if (tres == dos) {
    cout << '1' << endl;
  }

  return 0;
}
