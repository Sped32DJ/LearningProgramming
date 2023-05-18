#include <iostream>
#include <string>
#include <vector>
using namespace std;

int findwordfrequencies() {
  int numWords;
  cin >> numWords;

  vector<string> sentence(numWords);
  vector<int> vfrequency(numWords, 1);

  for (int i = 0; i < numWords; ++i) {
    cin >> sentence.at(i);
  }

  // fixes string, changes space for \n (may depricate this)
  /* for (int i = 0; i < sentence.size(); ++i) {
    if (isspace(sentence.at(i))) {
      sentence.at(i) = '\n'; // replaces space for \n
    }
  } */

  for (int i = 0; i < numWords; ++i) {
    if (sentence.at(i) != "") { // segment each words
      for (int j = i + 1; j < numWords; ++j) {
        if (sentence.at(j) == sentence.at(i)) {
          ++vfrequency.at(i); // Every word has an index
          ++vfrequency.at(j); // How does this work? idk -_-
        }
      }
      cout << sentence.at(i) << " - " << vfrequency.at(i) << endl;
    }
  }
  // Look at vector (vector works!)
  /* for (int i = 0; i < vfrequency.size(); ++i) {
    cout << vfrequency.at(i);
  }
  cout << endl; */
  // todo  find a way make a count for each word
  // ++vfrequency.at(i);
  // add the " - vfrequency.at(i)"
  //    make sure vfrequency index correalates to one word
  // read from the start of the index, until reaches '\n'
  //

  // check string, (this should probably be depricated)
}

int main() {
  findwordfrequencies();
  return 0;
}
