#include "Card.h"
#include <iostream>

using namespace std;

Card::Card() { // default value, 2 of Clubs
  suit = 'c';
  rank = 2;
}

/* Assigns the Card the suit and rank provided.
   suits: c = Clubs, d = Diamonds, h = Hearts, s = Spades
   If an invalid suit is provided, sets the suit to Clubs
   ranks: 1 - 13 (1 = Ace, 11 = Jack, 12 = Queen, 13 = King)
   If an invalid rank is provided, sets the rank to 2
   Accepts lower or upper case characters for suit
*/
Card::Card(char suit, int rank) {
  if (rank >= 1 && rank <= 13) {
    this->rank = rank;
  } else {
    this->rank = 2; // default
  }

  // Bulletproofing against edge-case scenarios
  if (isalpha(suit)) {
    this->suit = tolower(suit);
  } else {
    this->suit = 'c'; // default
  }
}

/* Returns the Card's suit
 */
char Card::getSuit() const { return tolower(suit); }

/* Returns the Card's rank as an integer
 */
int Card::getRank() const { return rank; }

/* Outputs a Card in the following format: Rank of Suit
   For example, if the rank is 3 and the suit is h: 3 of Hearts
   Or, if the rank is 1 and the suit is d: Ace of Diamonds
   Or, if the rank is 12 and the suit is c: Queen of Clubs
   etc.
*/
ostream &operator<<(ostream &out, const Card &rhs) {

  if (rhs.getRank() == 1) {
    out << "Ace of ";
  } else if (rhs.getRank() == 11) {
    out << "Jack of ";
  } else if (rhs.getRank() == 12) {
    out << "Queen of ";
  } else if (rhs.getRank() == 13) {
    out << "King of ";
  } else {
    out << rhs.getRank() << " of ";
  }

  if (rhs.getSuit() == 'c') {
    out << "Clubs";
  } else if (rhs.getSuit() == 'd') {
    out << "Diamonds";
  } else if (rhs.getSuit() == 'h') {
    out << "Hearts";
  } else if (rhs.getSuit() == 's') {
    out << "Spades";
  }

  return out;
}
