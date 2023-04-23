#include <iostream>
#include <string>
using namespace std;

int main() {
  int num, digit;
  string num2;

//  cin >> num;
  cin >> num2;
  // This is kinda lame lol
  /* if (num < 10000 && num >= 0) {
    if (num <= 9) {
      digit = 1;
    } else if (num <= 99) {
      digit = 2;
    } else if (num <= 999) {
      digit = 3;
    } else {
      digit = 4;
    }
  } */

  // chad Strings (not sure which one is more efficient)
  cout << "string: " << num2 << endl;
  cout << num2.length() << endl << endl;

  cout << num2.length() << " digit";
  if (num2.length() != 1) {
    cout << 's';
  }
  cout << endl;
  return 0;
}
