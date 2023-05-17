#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> vList;
  int input;

  while (input >= 0) { // this one works, somehow...
    vList.push_back(input);
    cin >> input;
  }

  if (vList.size() > 10) {
    cout << "Too many numbers";
  } else {
    cout << "Middle item: " << vList.at(vList.size() / 2);
  }
  cout << endl;

  /* while (vList.at(i) > 0) { // OUT OF RANGE ERRORS :sob:
    ++i;
    cin >> input;
    vList.push_back(input);
  }

  cout << vList.size();
  cout << endl << endl;

  cout << "Middle item: " << vList.at(vList.size() / 2) << endl; */

  return 0;
}
