#include <cstdlib> // Needed for srand
#include <ctime>   // Needed for time
#include <iostream>
#include <vector>

using namespace std; // For brevity, though it's generally not recommended

class Card {
public:
  Card(char suit, int rank);
  // Define any necessary member functions and operators here
};

class Deck {
public:
  Deck();
  // Define any necessary member functions here

private:
  vector<Card> theDeck;
};

Deck::Deck() {
  for (int i = 1; i < 53; ++i) {
    char suit;
    int rank;
    if (i < 14) {
      rank = i;
      suit = 'c';
    } else if (i < 27) {
      rank = i - 13;
      suit = 'd';
    } else if (i < 40) {
      rank = i - 27;
      suit = 'h';
    } else {
      rank = i - 40;
      suit = 's';
    }
    theDeck.push_back(Card(suit, rank));
  }
}

int main() {
  srand(time(nullptr)); // Seed the random number generator
  Deck deck;
  vector<Card> vHand;

  // For demonstration purposes, let's say we want to randomly select 5 cards
  for (int i = 0; i < 5; ++i) {
    int randomIndex =
        rand() %
        deck.size(); // Assuming you have a method to get the size of the deck
    vHand.push_back(deck[randomIndex]);
  }

  // Now let's print the cards in the hand (assuming you have defined the
  // operator<< for Card)
  for (size_t i = 0; i < vHand.size(); ++i) {
    cout << vHand[i] << endl;
  }

  return 0;
}
