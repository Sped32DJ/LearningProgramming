#include <iostream>
#include <string>
using namespace std;

int main() {
  cout << "Yes or no? [Y/n]: ";
  string input;

  getline(cin, input);

  if (input.empty() || input[0] == 'y' || input[0] == 'Y') {
    cout << "Hello" << endl;
  } else if (input[0] == 'n' || input[0] == 'N') {
    cout << "Bye" << endl;
  } else {
      cout << "Nice null" << endl;
  }
  /* The else if is not necessary since anything but empty/Y goes to No  */

  return 0;
}
