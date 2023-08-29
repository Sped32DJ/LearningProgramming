#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

#include "Card.h"
#include "Deck.h"

bool compareByRank(const Card &card1, const Card &card2);

// Returns true if vector of Cards passed in contains at least 2 Cards with
// the same rank.

void vSort(vector<Card> &hand);

bool hasPair(const vector<Card> &hand);

// Sends to output stream a hand of Cards on a single line,
// each Card separated by a comma.
// If the vector is empty, do not output anything.
// Example (vector size of 3): Ace of Spades, Two of Hearts, King of Clubs
ostream &operator<<(ostream &, const vector<Card> &);

int main() {
  srand(2222);
  Card test('h', 10);
  Card card1;
  string option;
  string fileName;
  vector<Card> vhand;
  vector<Card> dealtCards;
  size_t cardsPerHand;
  size_t numberOfDeals;
  ofstream outFS;

  cout << test.getRank() << ' ' << test.getSuit() << endl;
  cout << card1.getRank() << ' ' << card1.getSuit() << endl;
  cout << test << card1;

  cout << "Do you want to output all hand to a file? (Yes/No)";
  cin >> option;
  cout << endl;

  if (option == "Yes") {
    cout << "Enter name of output file: ";
    cin >> fileName;
    cout << endl;
    outFS.open(fileName);
  }

  cout << "Enter name of cards per hand: ";
  cin >> cardsPerHand;
  cout << endl;

  cout << "Enter number of deals (stimulations): ";
  cin >> numberOfDeals;
  cout << endl;

  cout << "Chances of receiving a pair in a hand of" << cardsPerHand
       << "cards is: "; // ispair calculation
  cout << endl;

  if (outFS.is_open()) {
    for (size_t i = 0; i < vhand.size(); ++i) {
      if (hasPair(vhand)) {
        cout << "Found Pair!! ";
        cout << vhand.at(i) << endl;
      } else {
        cout << vhand.at(i) << endl;
      }
    }
  }
  outFS.close();
  return 0;
}

bool compareByRank(const Card &card1, const Card &card2) {
  return card1.getRank() < card2.getRank();
}

void vSort(vector<Card> &hand) {
  int n = hand.size();
  for (size_t i = 0; i < n - 1; ++i) {
    for (size_t j = 0; j < n - i - 1; ++j) {
      if (number.at(j) > number.at(j + 1)) {
        int temp = number.at(j);
        number.at(j) = number.at(j + 1);
        number.at(j + 1) = temp;
      }
    }
  }
}

bool hasPair(const vector<Card> &hand) {
  // Any cards with same rank

  for (size_t i = 0; i + 1 < hand.size(); ++i) {
    if (hand.at(i).getRank() == hand.at(i + 1).getRank()) {
      return true;
    }
  }
  return false;
}
