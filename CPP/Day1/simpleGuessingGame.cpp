#include <iostream>
using namespace std;

int main() {

  int secretNum = 21;
  int guess;
  int guessCount = 0;
  int guessLimit = 3;
  bool outOfGuesses = false;

  while (secretNum != guess && !outOfGuesses) {
    if (guessCount < guessLimit) {
      cout << "Guess what number I'm thinking of [1-100]: ";
      cin >> guess;
      guessCount++;
    } else {
      outOfGuesses = true;
    }

    if (secretNum > guess) {
      cout << "Go Bigger!\n";
    } else if (secretNum < guess) {
      cout << "Go Smaller!\n";
    }
  }

  if (outOfGuesses) {
    cout << "You Lose!";
  } else {
    cout << "You guessed it!"
         << "in" << guessCount << " tries.";
  }

  return 0;
}
