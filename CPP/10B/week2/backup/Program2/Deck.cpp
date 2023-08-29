#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

#include "Deck.h"

/* Constructs a Deck of 52 cards:
   Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King of each suit.
   Cards should start off in this order with the order of suits being:
   Clubs, Diamonds, Hearts, Spades. So, the Card at the top of the
   Deck should be the Ace of Clubs.

   For best efficiency, the top of Deck should be stored at
   back end of vector.
*/
Deck::Deck() {
  // Loop through the 52 cards
  for (int i = 1; i <= 52; ++i) {
    // int rank = ((i - 1) % 13) + 1; // Ranks go from 1 to 13
    int rank = 13 - ((i - 1) % 13); // ranks go from 13 to 1

    char suit;

    // Determine the suit based on the card index
    if (i <= 13) {
      suit = 's'; // Clubs
    } else if (i <= 26) {
      suit = 'h'; // Diamonds
    } else if (i <= 39) {
      suit = 'd'; // Hearts
    } else {
      suit = 'c'; // Spades
    }

    /* if (i <= 13) {
      suit = 'c'; // Clubs
    } else if (i <= 26) {
      suit = 'd'; // Diamonds
    } else if (i <= 39) {
      suit = 'h'; // Hearts
    } else {
      suit = 's'; // Spades
    } */
    /* Card tempCard(suit, rank); */

    // Add the card to the deck
    theDeck.push_back(Card(suit, rank));
    /* theDeck.push_back(Card(tempCard.getSuit(), tempCard.getRank())); */
  }
}
/* Deals (returns) the top card of the deck.
   Removes this card from theDeck and places it in dealtCards.
   As mentioned in comments for the constructor,
   for best efficiency, the top card should come from the
   back end of vector.
*/
Card Deck::dealCard() {
  if (theDeck.empty()) {
    Card defaultCard;
    return defaultCard;
  }
  Card dealtCard = theDeck.back();

  /* dealtCards.push_back(theDeck.back()); */
  theDeck.pop_back();
  dealtCards.push_back(dealtCard);

  return dealtCard;
}

/* Places all cards back into theDeck and shuffles them into random order.
   Use shuffle function from algorithm library.
   To pass test harness, this function must go forward through dealtCards
   pushing each Card onto the back end of theDeck, then clear dealtCards.
   Do not use pop_back on dealtCards.
*/
/* void Deck::shuffleDeck() { // Nah, not this
  size_t seed = 2222;
  shuffle(theDeck.begin(), theDeck.end(), default_random_engine(seed));
} */
// FIX  "shuffleDeck() did not correctly shuffle Deck.
// Did you use random_shuffle function?"

/* void Deck::shuffleDeck() {
  vector<Card> combined;

  for (size_t i = 0; i < theDeck.size(); ++i) {
    combined.push_back(theDeck.at(i));
  }

  // combine dealtCards and theDeck into single vector
  for (size_t i = 0; i < dealtCards.size(); ++i) {
    combined.push_back(dealtCards.at(i));
  }
  size_t seed = 2222;
  default_random_engine rng(seed);

  // Shuffle combined vector
  // G++ told me to use shuffle instead of random_shuffle
  shuffle(combined.begin(), combined.end(), rng);
  //  random_shuffle(combined.begin(), combined.end());

  for (size_t i = 0; i < theDeck.size(); ++i) {
    theDeck.at(i) = combined.at(i);
  }
  dealtCards.clear();
} */

void Deck::shuffleDeck() {
  /* vector<Card> combined; */
  Card tempCard;
  // or do I reverse iterate?
  // (loop in ssh server)
  /* for (size_t i = 0; i < dealtCards.size(); ++i) {
    theDeck.push_back(theDeck.at(i));
  } */
  for (size_t i = 0; i < dealtCards.size(); ++i) {
    theDeck.push_back(dealtCards.at(i));
  }
  dealtCards.clear();

  /* size_t seed = 2222;
  default_random_engine rng(seed);
  shuffle(theDeck.begin(), theDeck.end(), rng); */
  random_shuffle(theDeck.begin(), theDeck.end());
}

/* returns the size of the Deck (how many cards have not yet been dealt).
 */
unsigned Deck::deckSize() const { return theDeck.size(); }
