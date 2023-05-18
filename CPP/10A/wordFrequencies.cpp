#include <iostream>
#include <string>
#include <vector>
using namespace std;

int FindWordFrequencies() {
  int size;
  string sentence;
  vector<int> vlist;
  vector<int> vFrequency(size);

  cin >> size;
  getline(cin, sentence);

  /* for (int i; i < size; ++i) {
  } */

  // nested forloop, replace space for \n
  for (int i = 0; i < sentence.size(); ++i) {
    if (isspace(sentence.at(i))) {
      sentence.at(i) = '\n';
    }
    for (int j = 0; j < sentence.size(); ++j) {
      cout << " - "
    }
  }
  // TODO  Find a way make a count for each word
  // ++vFrequency.at(i);
  // add the " - vFrequency.at(i)"
  //    Make sure vFrequency correalates to one word
  // Read from the start of the index, until reaches '\n'

  // check string, (this should probably be depricated)
  cout << sentence << endl;
}

int main() {
  FindWordFrequencies();
  return 0;
}
