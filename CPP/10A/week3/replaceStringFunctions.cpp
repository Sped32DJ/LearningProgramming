#include <iostream>:
#include <string>
using namespace std;

int main() {
  string s;
  getline(cin, s);

  if (s.find( "tbh" ) != string::npos){
      s.replace(s.find("tbh"), 3, "to be honest");
  } else {
    cout << "No matches";
  }

  cout << s;
  cout << endl;

  return 0;
}
