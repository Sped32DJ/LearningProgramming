#include <iostream>
using namespace std;

int main() {

  int secretNum = 21;
  int guess;
  int guessCount = 0;
  int guessLimit = 3;
  int one = 1;
  bool outOfGuesses = false;

  /* while (secretNum != guess && !outOfGuesses) {
    if (guessCount < guessLimit && !outOfGuesses) {
      cout << "Guess what number I'm thinking of [1-100]: ";
      cin >> guess;
      guessCount++;
    } else if (secretNum <= guess) {
      cout << "Go smaller!\n";
    } else if (secretNum >= guess) {
      cout << "Go Bigger!\n";
    } else {
      outOfGuesses = true;
      cout << "You lose!";
    } */
  while (secretNum != guess && !outOfGuesses) {
    if (guessCount < guessLimit) {
      cout << "Guess what number I'm thinking of [1-100]: ";
      cin >> guess;
      guessCount++;
    } else {
      outOfGuesses = true;
    }

    if (secretNum > guess) { // Combine this with the if statement above, you get bugs :)
      cout << "Go Bigger!\n";
    } else if (secretNum < guess) {
      cout << "Go Smaller!\n";
    }
  }

  if (outOfGuesses) {
    cout << "You Lose!" << endl;
  } else {
    cout << "You guessed it!\n"
         << "Only took you " << guessCount << " tries." << endl;
  }
  return 0;
  /* return guess, secretNum; */
}

/* int second(){ */

/* Simplified version of the code
 TODO  Learn how to use return to work here on the second function*/ /*
while (secretNum != guess) {
  cout << "Enter guess: ";
  cin >> guess;
}
  cout << guess << endl;
  return 0;
} */
