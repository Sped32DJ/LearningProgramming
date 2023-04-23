#include <iostream>
#include <string>
using namespace std;

int main() {
  string s, s1;
  getline(cin, s);
  getline(cin, s1);

  if (s == s1) {
    cout << "Both phrases match";
  } else if (s1.find(s) != string::npos) {
    cout << s << " is found within " << s1;
  } else if (s.find(s1) != string::npos){
    cout << s1 << " is found within " << s;
  } else {
    cout << "No matches";
  }
  cout << endl;

  return 0;
}
