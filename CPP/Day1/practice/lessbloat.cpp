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
  int round = 1;
  string choice;
  string pause;

  cout << "How many letters? (";
  cout << minLetters << "-" << maxLetters << "): ";
  cin >> howManyLetters;

  cout << "How many positions? (";
  cout << minPositions << "-" << maxPositions << "): ";
  cin >> howManyPositions;

  std::cin.sync();
  getline(cin, choice);
  cout << "Yes or no? [Y/n]: ";
  getline(cin, pause); // I can not explain why this solution work :sob:
  cout << "Choice: " << choice << "\npause: " << pause << endl; // Debugging

  if (choice.empty() || choice[0] == 'y' || choice[0] == 'Y') {
    std::cout << "Hello" << std::endl;
  } else {
    std::cout << "Bye" << std::endl;
  }

  cout << "\n"
       << "\n Letters: " << howManyLetters
       << "\n Positions: " << howManyPositions << "\n choice: " << choice
       << endl;

  return 0;
}
