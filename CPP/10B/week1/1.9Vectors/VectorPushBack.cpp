#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> intVector;
  int value;
  int i;
  bool isOdd;

  cin >> value;
  while (value != 0) {
    intVector.push_back(value);
    cin >> value;
  }

  if (intVector.back() % 2 != 0) {
    for (i = intVector.size() - 1; i >= 0; --i) {
      if (intVector.at(i) % 2 != 0) {
        cout << intVector.at(i) << endl;
      }
    }
  } else {
    for (i = 0; i < intVector.size(); ++i) {
      if (intVector.at(i) % 2 == 0) {
        cout << intVector.at(i) << endl;
      }
    }
  }

  return 0;
}

/* #include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> dataVector;
  int value;
  int i;

  cin >> value;
  while (value != 0) {
    dataVector.push_back(value);
    cin >> value;
  }

  for (i = dataVector.size() - 1; i >= 0; --i) {
    if (dataVector.at(i) % 2 != 0) {
      cout << dataVector.at(i) << endl;
    }
  }

  return 0;
} */

/* #include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> numberVector;
  int value;
  int i;

  cin >> value;
  while (value != -1) {
    numberVector.push_back(value);
    cin >> value;
  }

 // int sum = numberVector.back();
  for (i = 0; i < numberVector.size(); ++i) {
 //   sum += numberVector.at(i);
    cout << numberVector.at(i) - numberVector.back() << endl;
  }

  return 0;
} */
/* #include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<string> wordVector;
  string value;
  int i;

  cin >> value;
  while (value != "end") {
    wordVector.push_back(value);
    cin >> value;
  }

  for (i = 0; i < wordVector.size(); ++i) {
    cout << wordVector.at(i) << endl;
  }

  return 0;
} */
