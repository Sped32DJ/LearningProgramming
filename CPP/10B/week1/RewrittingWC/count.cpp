#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  string filename;
  string line;

  filename = argv[1];

  ifstream fin(filename);

  if (!fin.is_open()) {
    cout << "Error opening " << filename << endl;
    return EXIT_FAUILURE;
  }

  int numLines = 0;
  int numChars = 0;
  int numWords = 0;
  string word;

  string line;
  char ch = 'z';
  istringstream inSS;

  while (getline(fin, line)) {
    ssin.str(line);

    while (inSS >> word) {
      ++numWords;
    }
    inSS.clear();

    ++numLines;
    numChars += line.size() + 1;
  }

  /* while (fin >> word) {
    ++numWords;
  } */

  /* while (fin.get(ch)) { // Reads whitespace
    cout << ch;
    ++numChars;
  } */

  cout << "Lines: " << numLines << endl
       << "Words: " << numWords << endl
       << "Chars: " << numChars << endl;

  return 0;
}
