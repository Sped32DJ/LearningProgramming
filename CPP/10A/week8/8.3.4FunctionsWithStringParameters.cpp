#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
using namespace std;

void SearchPattern(string inputString) {
  if (inputString.find("mis")) {
    cout << inputString << " does not contain mis.";
  } else {
    cout << inputString << " contains mis.";
  }
  cout << endl;
}

int main() {
  int i;
  string inputString;

  cin >> inputString;

  SearchPattern(inputString);

  return 0;
}

/* void InspectCharacters(const string &inputString, char x,
                       vector<bool> &results) {
  results.resize(inputString.size(), false);
  for (size_t i = 0; i < inputString.size(); ++i) {
    if (inputString.at(i) == x) {
      results.at(i) = true;
    }
  }
}

int main() {
  string inputString;
  int i;
  char x;
  vector<bool> results;

  cin >> inputString;
  cin >> x;

  InspectCharacters(inputString, x, results);

  for (i = 0; i < results.size(); ++i) {
    if (results.at(i)) {
      cout << inputString.at(i) << " is equal to " << x << endl;
    } else {
      cout << inputString.at(i) << " is not equal to " << x << endl;
    }
  }

  return 0;
} */
