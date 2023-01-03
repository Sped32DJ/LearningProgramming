#include <iostream>

using namespace std;

int main() {

  cout << "Decryptix.\t Copyright 1999 Liberty " << endl;
  cout << "Associates, Inc. Version 0.2\n " << endl;
  cout << "There are two ways to play Decryptix: ";
  cout << " either you can guess a pattern I create, ";
  cout << "or I can guess your pattern.\n\n";

  cout << "If you are guessing, I will think of a\n ";
  cout << "pattern of letters (e.g., abcde).\n\n";

  cout << "On each turn, you guess the pattern and\n";
  cout << " I will tell you how many letters you \n";
  cout << "got right, and how many of the correct\n";
  cout << " letters were in the correct position.\n\n";

  cout << "The goal is to decode the puzzle as quickly\n";
  cout << "as possible. You control how many letters \n";
  cout << "can be used and how many positions\n";
  cout << " (e.g., 5 possible letters in 4 positions) \n";
  cout << "as well as whether or not the pattern might\n";
  cout << " contain duplicate letters (e.g., aabcd).\n\n";

  cout << "If I'm guessing, you think of a pattern \n";
  cout << "and score each of my answers.\n\n" << endl;
  const int minLetters = 2;
  const int maxLetters = 10;
  const int minPositions = 3;
  const int maxPositions = 10;
  int howManyLetters = 0, howManyPositions = 0;
  bool duplicatesAllowed = false;
  int round = 1;

  cout << "How many letters? (";
  cout << minLetters << "-" << maxLetters << "): ";
  cin >> howManyLetters;

  cout << "How many positions? (";
  cout << minPositions << "-" << maxPositions << " ): ";
  cin >> howManyPositions;

  char y = 'y';
  char n = 'n';
  char choice; // Probably better as a bool
  cout << "Allow duplicates (Y/n): ";
  cin >> choice;
  if (choice == y) {
    cout << "You said yes" << endl;
  } else if (choice == n) {
    cout << "lol no" << endl;
  } else {
    cout << "Nice null" << endl;
  }

  return 0;
}
