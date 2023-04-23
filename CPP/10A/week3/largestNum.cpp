#include <iostream>
using namespace std;

int main() {

  int uno, dos, tres, i;
  cin >> uno >> dos >> tres;
  i = 0;

  if (uno >= dos && uno >= tres) {
    cout << uno << endl;
    i++;
  }
  if (dos >= uno && dos >= tres) {
    if (i >= 1) {
    } else {
      cout << dos << endl;
    }
    i++;
  }
  if (tres >= uno && tres >= uno) {
    if (i >= 1) {
    } else {
      cout << tres << endl;
    }
    i++;
  }
  cout << i << endl;

  return 0;
}
