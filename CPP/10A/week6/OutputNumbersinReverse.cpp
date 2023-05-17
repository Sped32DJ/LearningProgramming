#include <iostream>
#include <vector>
using namespace std;

int main() {
  int size;

  cin >> size;

  vector<int> vUserInts(size);

  // Filling vector
  for (int i = 0; i < size; ++i) {
    cin >> vUserInts.at(i);
  }

  // output, reverse iteration
  for (int i = vUserInts.size() - 1; i >= 0; --i) {
    cout << vUserInts.at(i) << ',';
  }
  cout << endl;

  return 0;
}
