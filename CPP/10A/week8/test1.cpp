#include <string>
#include <iostream>
#include <vector>
using namespace std;

void findWordFrequencies() {
  int numWords;
  cin >> numWords;

  vector<string> sentence(numWords);
  vector<int> vFrequency(numWords, 1);

  for (int i = 0; i < numWords; ++i) {
    cin >> sentence.at(i);
  }

  for (int i = 0; i < numWords; ++i) {
    if (sentence.at(i) != "") {
      for (int j = i + 1; j < numWords; ++j) {
        if (sentence.at(j) == sentence.at(i)) {
          ++vFrequency.at(j); // Increment the frequency of the word at index j
        }
      }
    }
  }

  for (int i = 0; i < numWords; ++i) {
    if (sentence.at(i) != "") {
      cout << sentence.at(i) << " - " << vFrequency.at(i) << endl;
    }
  }
}

int main() {
  findWordFrequencies();
  return 0;
}
