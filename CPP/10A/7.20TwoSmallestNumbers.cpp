#include <iostream>
#include <vector>
using namespace std;

// please don't even code like this
int findminval() {
  int size, current, min1, min2, index;
  cin >> size;
  vector<int> vMinVal;
  min1 = 66;
  min2 = 66;

  // fill vector
  for (int i = 0; i < size; ++i) {
    cin >> current;
    vMinVal.push_back(current);
    /* cout << vMinVal.at(i) << ' ' ; // vector filled in */
  }

  // two loops that find the min each time
  for (int i = 0; i < size; ++i) {
    if (vMinVal.at(i) < min1) {
      min1 = vMinVal.at(i);
      index = i;
    }
  }
  /* vMinVal.erase(index); */

  // find min2
  for (int i = 0; i < vMinVal.size(); ++i) {
    if (vMinVal.at(i) < min2 && vMinVal.at(i) > min1) {
      min2 = vMinVal.at(i);
    }
  }

  // while loop that organizes numbers until they are sequential kek
  // Least efficient meme

  /* cout << vMinVal.at(0) << " and " << vMinVal.at(1) << endl; */
  cout << min1 << " and " << min2 << endl;
}

int main() {
  findminval();
  return 0;
}
