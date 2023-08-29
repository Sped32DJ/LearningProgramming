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
ostream &operator<<(ostream &os, const vector<Card> &hand);

int main() {
  Deck deck;
  srand(2222);
  vector<Card> vHand;

  // Fill hand with cards
  cout << deck.deckSize() << endl;
  while (deck.deckSize() > 0) {
    vHand.push_back(deck.dealCard());
  }

  for (size_t i = 0; i < vHand.size(); ++i) {
    cout << vHand.at(i) << endl;
  }
  cout << deck.deckSize() << endl;

  return 0;
}

bool compareByRank(const Card &card1, const Card &card2) {
  return card1.getRank() < card2.getRank();
}

void vSort(vector<Card> &hand) {
  int n = hand.size();
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (hand.at(j).getRank() > hand.at(j + 1).getRank()) {
        Card temp = hand.at(j);
        hand.at(j) = hand.at(j + 1);
        hand.at(j + 1) = temp;
      }
    }
  }
}

ostream &operator<<(ostream &os, const vector<Card> &hand) {
  if (!hand.empty()) {
    os << hand.at(0);
    for (size_t i = 1; i < hand.size(); ++i) {
      os << ", " << hand.at(i);
    }
  }
  return os;
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
