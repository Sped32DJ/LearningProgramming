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
    if (guessCount < guessLimit && guessCount < one) { // This works
      cout << "Guess what number I'm thinking of [1-100]: ";
      cin >> guess;
      guessCount++;
    } else if (secretNum > guess) {
      cout << "Go Bigger!\n";
      cin >> guess;
      guessCount++;
    } else if (secretNum < guess) {
      cout << "Go Smaller!\n";
      cin >> guess;
      guessCount++;
    } else if (secretNum = guess) {
      cout << "You win!\tpenis\n";
      cout << "Took " << guessCount << "Tries :)" << endl;
    } else {
      outOfGuesses = true;
      cout << "You lose!";
    }
  }

  if (outOfGuesses) {
    cout << "You Lose!";
  } else {
    cout << "You guessed it!"
         << "in" << guessCount << " tries.";
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
