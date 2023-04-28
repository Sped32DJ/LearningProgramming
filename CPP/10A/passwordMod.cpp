#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  char character;
  int i;

  cin >> s;

  // P A S S
  // interate letter by letter
  for (i = 0; i < s.size(); i++) {
    character = s[i];
    if (character == 'i') {
      character = '1';
    }
    if (character == 'a') {
      character = '@';
    }
    if (character == 'm') {
      character = 'M';
    }
    if (character == 'B') {
      character = '8';
    }
    if (character == 's') {
      character = '$';
    }
    cout << character; // prints out char by char, doesn't print out string
  }

  /* s.append('!'); */
  cout << '!' << endl; // Ok, this is cheating -__-

  return 0;
}
