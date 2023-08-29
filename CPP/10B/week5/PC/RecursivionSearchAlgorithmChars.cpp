#include <iostream>
#include <vector>
using namespace std;

void Search(vector<char> dataList, char target, int firstIndex, int lastIndex) {
  int midIndex;
  int rangeSize;
  char midValue;

  rangeSize = (lastIndex - firstIndex) + 1;
  midIndex = (firstIndex + lastIndex) / 2;
  midValue = dataList.at(midIndex);

  if (target == midValue) {
    cout << target << " is found at index " << midIndex << endl;
  } else if (rangeSize == 1) {
    cout << target << " is not in the list" << endl;
  } else {

    if (target < midValue) {
      cout << "search lower half" << endl;
      Search(dataList, target, firstIndex, midIndex);
    } else {
      cout << "search upper half" << endl;
      Search(dataList, target, midIndex + 1, lastIndex);
    }
  }
}

int main() {
  char target;
  vector<char> dataList;
  int numData;
  int i;
  char item;

  cin >> target;
  cin >> numData;
  for (i = 0; i < numData; ++i) {
    cin >> item;
    dataList.push_back(item);
  }
  Search(dataList, target, 0, dataList.size() - 1);

  return 0;
}
