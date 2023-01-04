#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  const int minLetters = 2;
  const int maxLetters = 10;
  const int minPositions = 3;
  const int maxPositions = 10;
  int howManyLetters = 0, howManyPositions = 0;
  bool duplicatesAllowed = false;
  string input;

  cout << "How many letters? (";
  cout << minLetters << "-" << maxLetters << "): ";
  cin >> howManyLetters;

  cout << "How many positions? (";
  cout << minPositions << "-" << maxPositions << "): ";
  cin >> howManyPositions;

  cout << "Yes or no? [Y/n]: ";
  getline(cin, choice);
  choice.erase(remove(choice.begin(), choice.end(), ' '), choice.end());

  if (choice.empty() || choice[0] == 'y' || choice[0] == 'Y') {
    cout << "Hello" << endl;
  } else if (choice[0] == 'n' || choice[0] == 'N') {
    cout << "Bye" << endl;
  } else {
    cout << "Nice null" << endl;
  }

  return 0;
}
