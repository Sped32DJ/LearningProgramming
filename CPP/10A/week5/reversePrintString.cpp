#include <iostream>
using namespace std;

// Please, for the love of all that is holy
// Don't program like this
// Ever, in your life
// I slept 5 hours today, why am I still here :sob:
int main() {

  string s;

  getline(cin, s);
  while (s != "done" || s != "Done") {
    for (int i = s.size() - 1; i >= 0; --i) {
      /* cout << i; */
      cout << s.at(i);
    }
    cout << endl;
    getline(cin, s);
    if (s == "done" || s == "Done" || s.size() == 1) {
      break;
    }
  }

  return 0;
}
