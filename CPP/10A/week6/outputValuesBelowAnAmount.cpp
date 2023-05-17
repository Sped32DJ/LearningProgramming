#include <iostream>
#include <vector>
using namespace std;

int main() {
  int min, max, size, input;
  cin >> size; // cin the firt num
  ++size;
  vector<int> vlist(size);

  // fill vector, starts filling after second input
  for (int i = 0; i < size; ++i) {
    cin >> input;
    vlist.at(i) = input;
  }

  // min and max
  min = vlist.at(0);
  max = vlist.at(vlist.size() - 1);

  // Testing to see if the vector was filled out (it was)
  /* for (int i = 0; i < size; ++i) {
    cout << vlist.at(i) << ' ';
  }
  cout << endl; */


  // output; not working kekw
  for (int i = 0; i < size; ++i) {
    if (vlist.at(i) >= min && vlist.at(i) < max) {
      cout << vlist.at(i) << ',';
    }
  }
  cout << endl;

  return 0;
}
