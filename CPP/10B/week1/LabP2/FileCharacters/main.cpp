#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// Place charCnt prototype (declaration) here
int charCnt(string file, char c);

int main() {
  string filename;
  char ch;
  int chCnt = 0;

  cout << "Enter the name of the input file: ";
  cin >> filename;
  cout << endl;
  cout << "Enter a character: ";
  cin.ignore(); // ignores newline left in stream after previous input statement
  cin.get(ch);  // line 20
  cout << endl;

  chCnt = charCnt(filename, ch);
  if (chCnt != -1) {
    cout << "# of " << ch << "'s: " << chCnt << endl;
  }

  return 0;
}

int charCnt(string file, char c) {
  ifstream inFS;
  int count = 0;
  char currentChar;

  inFS.open(file);
  if (inFS.is_open()) {
    while (inFS.get(currentChar)) { // inFS.get(), very vital
      if (currentChar == c) {
        ++count;
      }
    }
  } else {
    cout << "Error opening " << file << endl;
    return -1;
  }
  return count;
}

// Place charCnt implementation here
