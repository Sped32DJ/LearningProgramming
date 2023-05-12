#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> hourlyPrices;
  int i;
  int vecVals;

  cin >> vecVals;
  // Creates a vector of size vecVals and initialize all values to 0
  hourlyPrices.resize(vecVals);

  for (i = 0; i < hourlyPrices.size(); ++i) {
    cin >> hourlyPrices.at(i);
  }

  for (i = hourlyPrices.size() - 1; i >= hourlyPrices.size() / 2; --i) {
    if (i - 1 > 0) {
      cout << hourlyPrices.at(i);
      cout << " | ";

    } else {
      cout << hourlyPrices.at(i);
    }
  }
  cout << endl;

  return 0;
}

// exercise 2
int kek() {
  for (i = averageScore.size() - 1; i > averageScore.size() / 2 - 1; --i) {
    cin >> averageScore.at(i)
  }

  return 2;
}

// Exercise 3
int exerciseTree() {

  numMatches = 0;
  for (i = 0; i < averageScore.size(); ++i) {
    if (averageScore.at(i) == 5) {
      ++numMatches;
    }
  }

  return 3;
}
