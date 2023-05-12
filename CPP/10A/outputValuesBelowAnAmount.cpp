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
    vlist.push_back(input);
  }

  // min and max
  min = vlist.at(0);                // broken
  max = vlist.at(vlist.size() - 1); // Working

  // debugging
  cout << "min max size++ input .size()\n";
  cout << "debugging: " << min << ' ' << max << ' ' << size << ' ' << input
       << ' ' << vlist.size() << endl;

  // output; not working kekw
  cout << "Output for code: \n";
  for (int i = 0; i < size; ++i) {
    if (vlist.at(i) > min && vlist.at(i) < max) {
      cout << vlist.at(i) << ' ';
    }
  }
  cout << endl;

  return 0;
}
