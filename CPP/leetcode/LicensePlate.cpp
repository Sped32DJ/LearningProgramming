#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

bool isTwoChars(const string &str) {
  return isalpha(str.at(0)) && isalpha(str.at(1));
}

bool expectedRange(const string &str) {
  return str.size() > 2 && str.size() < 6;
}

int main() {
  string input;
  getline(cin, input);

  if (isTwoChars(input) && expectedRange(input)) {
    cout << "Valid License plate" << endl;
  } else {
    cout << "invalid License plate" << endl;
  }
  return 0;
}
