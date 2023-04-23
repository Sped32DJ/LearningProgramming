#include <iostream>
#include <string>
using namespace std;

int main() {
  string s, s1;
  getline(cin, s);
  /* getline(cin, s1); */

  s.append(" The end");
  s.push_back('!');
  s = s + " That's all.";
  /* s.resize(10); Length = 10 */

  // cap the first letter if not upper
  if (!isupper(s.at(0))) {
    s.at(0) = toupper(s.at(0));
  }

  if (s.find("tbh") != string::npos) {
    s.replace(s.find("tbh"), 3, "to be honest");
  } else {
    cout << "No matches";
  }

  /* if (input.find("fire")) {
    cout << input << " is found within " << input2;
  } else if (input == input2) {
    cout << "Both phrases match";
  } else {
    cout << "No matches";
  } */
  cout << s << endl;

  // prints out what is within that index
  cout < s.substr(4, 7) << endl;

  return 0;
}
