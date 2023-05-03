#include <iostream>
#include <string>
using namespace std;

int main() {

  string s;
  int i;

  getline(cin, s);

  for (i = s.find('.') + 1; i >= s.size(); ++i){
      cout << s.at(i) << endl;
  }
    /* for (i = s.size() - 1; i >= 0; --i) {
      cout << s.at(i) << endl;
    } */

  return 0;
}
