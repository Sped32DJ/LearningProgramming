#include <iostream>
#include <string>
using namespace std;

int main() {
  int baseDigit, headDigit;
  cin >> baseDigit >> headDigit; // 0 1

  string topLine     = string(5, ' ') + to_string(headDigit) + '\n';
  string secondLine  = string(5, ' ') + to_string(headDigit) + to_string(headDigit) + '\n';
  string middleLines = string(5, to_string(baseDigit)[0]) + string(3, to_string(headDigit)[0]) + '\n' +
                       string(5, to_string(baseDigit)[0]) + string(4, to_string(headDigit)[0]) + '\n' +
                       string(5, to_string(baseDigit)[0]) + string(3, to_string(headDigit)[0]) + '\n';
  string bottomLine  = string(5, ' ') + to_string(headDigit) + to_string(headDigit) + '\n' +
                       string(5, ' ') + to_string(headDigit) + '\n';

/* Matches this output, line by line
     1
     11
00000111
000001111
00000111
     11
     1
 */

  cout << topLine << secondLine << middleLines << bottomLine;
  return 0;
}
