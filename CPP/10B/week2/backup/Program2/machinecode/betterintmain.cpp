int main() {
  srand(static_cast<unsigned int>(
      time(nullptr))); // Seed the random number generator
  vector<Card> vHand;
  size_t cardsPerHand;
  size_t numberOfDeals;
  size_t pairsFound = 0;
  ofstream outFS;

  cout << "Do you want to output all hands to a file? (Yes/No): ";
  string option;
  cin >> option;
  cout << endl;

  if (option == "Yes" || option == "yes" || option == "YES") {
    string fileName;
    cout << "Enter name of output file: ";
    cin >> fileName;
    cout << endl;
    outFS.open(fileName);
  }

  cout << "Enter number of cards per hand: ";
  cin >> cardsPerHand;
  cout << endl;

  cout << "Enter number of deals (simulations): ";
  cin >> numberOfDeals;
  cout << endl;

  for (size_t i = 0; i < numberOfDeals; ++i) {
    vHand.clear();
    Deck deck;
    deck.shuffleDeck();

    for (size_t j = 0; j < cardsPerHand; ++j) {
      vHand.push_back(deck.dealCard());
    }

    if (hasPair(vHand)) {
      pairsFound++; // Increment the count of pairs found
    }

    if (outFS.is_open()) {
      if (hasPair(vHand)) {
        outFS << "Found Pair!! ";
      } else {
        outFS << setw(14) << " ";
      }

      outFS << vHand;
    }
    outFS << endl;
  }

  if (outFS.is_open()) {
    outFS.close();
  }

  double pairProb = (static_cast<double>(pairsFound) / numberOfDeals) * 100.0;
  cout << "Chances of receiving a pair in a hand of " << cardsPerHand
       << " cards is: " << pairProb << "%" << endl;

  return 0;
}
