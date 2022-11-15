#include <cmath>
#include <iostream>
// All the cmath stuff refuses to compile lol
using namespace std;

int main() {

  int wnum = 5;
  double dnum = 5.5;

  cout << round(5.8);
  cout << fmax(3, 10);
  cout << 10.0 / 3.0 << endl;
  cout << 10 / 3 << endl;
  wnum++;
  wnum /= 80;
  cout << wnum;
  cout << 5 + 6 << endl;
  cout << 5 * 6 << endl;
  cout << 10 % 3 << "10 mod 3" << endl;
  cout << 4 + 5 * 10 << dnum << endl;
  cout << (4 + 5) * 10 << endl;

  return 0;
}
