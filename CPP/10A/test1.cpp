#include <iostream>
#include <vector>
using namespace std;

/* Define your function here */
int GetMinimumInt(const vector<int> &listInts) {
  int minval = listInts.at(0);
  for (size_t i = 0; i < listInts.size(); ++i) {

    if (minval > listInts.at(i)) {
      minval = listInts.at(i);
    }
  }
  return minval;
}

int main() {
  vector<int> vList;
  /* cout << "The minimun is " << GetMinimumInt(vList) << endl; */
  size_t length;
  size_t input;
  cin >> length;
  for (size_t i = 0; i < length; ++i) {
    cin >> input;
    vList.push_back(input);
    cout << " " << vList.at(i) - GetMinimumInt(vList);
  }

  return 0;
}
