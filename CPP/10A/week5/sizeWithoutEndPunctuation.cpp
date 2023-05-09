#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  size_t punc = 0; // Yes, these are flipped, problem?
  size_t alp = 0;
  // Add more variables as needed

  getline(cin, s); // Gets entire line, including spaces.

  /* if (s.at(s.size() - 1) == '.') {
    cout << s.size() - 1;
  } else {
    cout << s.size();
  }
  cout << endl; */

  // how many non periods (both need a counter)
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '.' || s[i] == '!' || s[i] == '?' ) {
      ++punc;
      /* cout << s[i]; */
    } else {
      ++alp;
    }
  }
  cout << alp << endl;
  cout << punc << endl;

  // how many periods

  return 0;
}
