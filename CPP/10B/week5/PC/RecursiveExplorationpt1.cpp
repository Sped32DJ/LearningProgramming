#include <iostream>
#include <vector>
using namespace std;

void ScrambleNums(vector<int> remainNums, vector<int> scramNums) {
  vector<int> tmpRemainNums;
  int tmpRemovedNum;
  int i;

  if (remainNums.size() == 0) {
    cout << scramNums.at(0);
    cout << scramNums.at(1);
    cout << scramNums.at(2) << endl;
  } else {
    for (i = 0; i < remainNums.size(); ++i) {
      tmpRemainNums = remainNums; // Make a copy.
      tmpRemovedNum = tmpRemainNums.at(i);
      tmpRemainNums.erase(tmpRemainNums.begin() + i); // Remove element at i
      scramNums.push_back(tmpRemovedNum);
      ScrambleNums(tmpRemainNums, scramNums);
      scramNums.erase(scramNums.end() - 1); // Remove last element
    }
  }
}

int main() {
  vector<int> numsToScramble;
  vector<int> resultNums;

  numsToScramble.push_back(9);
  numsToScramble.push_back(7);
  numsToScramble.push_back(6);

  ScrambleNums(numsToScramble, resultNums);

  return 0;
}
