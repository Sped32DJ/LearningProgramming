#include <iostream>
#include <string>
using namespace std;

int main() {
  string userString;

  cin >> userString;
  // masculine urge to not use .isdigit(i)
  for (int i = 0; i < userString.size(); i++) {
    if (userString[i] < '0' || userString[i] > '9') {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;

  return 0;
}
