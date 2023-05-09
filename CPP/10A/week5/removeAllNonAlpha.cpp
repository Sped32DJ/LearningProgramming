#include <iostream>
using namespace std;

int main() {

  string s;
  getline(cin, s);

  for (size_t i = 0; i < s.size(); ++i) {
    if (isalpha(s.at(i))) {
      cout << s[i];
    }
  }
  cout << endl;

  return 0;
}
