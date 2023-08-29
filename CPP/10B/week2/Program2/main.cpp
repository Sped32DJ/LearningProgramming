#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

#include "Card.h"
#include "Deck.h"

bool compareByRank(const Card &card1, const Card &card2);

// Returns true if vector of Cards passed in contains at least 2 Cards with
// the same rank.

bool hasPair(const vector<Card> &hand);

// Sends to output stream a hand of Cards on a single line,
// each Card separated by a comma.
// If the vector is empty, do not output anything.
// Example (vector size of 3): Ace of Spades, Two of Hearts, King of Clubs
ostream &operator<<(ostream &os, const vector<Card> &hand);

int main() {
  srand(2222);

  size_t cardsPerHand;
  size_t numberOfDeals;
  size_t pairsFound = 0;
  ofstream outFS;

  cout << "Do you want to output all hands to a file? (Yes/No)";
  string option;
  cin >> option;
  cout << endl;

  if (option == "Yes" || option == "yes" || option == "YES") {
    cout << "Enter name of output file: ";
    string fileName;
    cin >> fileName;
    cout << endl;
    outFS.open(fileName);
  }

  // Do we calculate a single hand or multiple?
  // Or take the sample from a single hand with 5 cards?
  cout << "Enter number of cards per hand: ";
  cin >> cardsPerHand;
  cout << endl;
  // TODO  Generates a deck this cardsPerHand
  /* deck.shuffleDeck(); */

  // TestBech
  /* cout << "Testing\n";
  Deck testDeck;
  vector<Card> vTemp;

  for (size_t i = 0; i < 52; ++i) {
    vTemp.push_back(testDeck.dealCard());
    cout << ' ' << vTemp.at(i).getRank() << ' ' << vTemp.at(i).getSuit()
         << endl;
  } */

  cout << "Enter number of deals (simulations): ";
  cin >> numberOfDeals;
  cout << endl;

  // [i] Does the correct amount of calculations
  // [j] The amount of cardsPerHand
  // FIX  Forloop does more and more values
  // I think I must declare a new deck, and shuffleDeck
  // Straight up not shuffling
  Deck deck;
  /* for (size_t i = 0; i < numberOfDeals; ++i) {
    vector<Card> vHand;

    // FIX  if this doesn't, then what does?
    for (size_t z = 0; z < i; ++z) {
      deck.shuffleDeck();
    }
    // Filling vHand after shuffling new deck
    for (size_t j = 0; j < cardsPerHand; ++j) {
      vHand.push_back(deck.dealCard());
    }

    if (hasPair(vHand)) {
      ++pairsFound;
    }

    if (outFS.is_open()) {
      if (hasPair(vHand)) {
        outFS << "Found Pair!! ";
      } else {
        outFS << setw(13) << " ";
      }
      outFS << vHand;
    }
    outFS << endl;
  } */
  // Redoing above
  for (size_t i = 0; i < numberOfDeals; ++i) {
    vector<Card> vHand;
    deck.shuffleDeck();
    for (size_t j = 0; j < cardsPerHand; ++j) {
      vHand.push_back(deck.dealCard());
    }

    if (hasPair(vHand)) {
      ++pairsFound;
    }
    if (outFS.is_open()) {
      if (hasPair(vHand)) {
        outFS << "Found Pair!! ";
      } else {
        outFS << setw(13) << " ";
      }
      outFS << vHand;
    }
    outFS << endl;
  }

  // close outFS
  if (outFS.is_open()) {
    outFS.close();
  }

  double pairProb = ((static_cast<double>(pairsFound) / numberOfDeals) * 100.0);

  cout << "Chances of receiving a pair in a hand of " << cardsPerHand
       << " cards is: " << pairProb << "%" << endl;

  return 0;
}

bool compareByRank(const Card &card1, const Card &card2) {
  if (card1.getRank() == card2.getRank()) {
    return true;
  } else {
    return false;
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
  vector<Card> tempHand = hand;
  sort(tempHand.begin(), tempHand.end(), compareByRank);
  bool isPair = false;

  for (size_t i = 0; i + 1 < tempHand.size(); ++i) {
    if (compareByRank(tempHand.at(i), tempHand.at(i + 1))) {
      isPair = true;
    }
    if (i == 1) {
      if (compareByRank(tempHand.at(i), tempHand.at(i + 2))) {
        isPair = true;
      }
    }
  }
  return isPair;
}
