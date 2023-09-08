#include <iostream>

using namespace std;

class Sort {
private:
  int indexSmallest;

public:
  void SortLowToHigh();
};

void Sort::SortLowToHigh(int numbersSize,vector<int> &numbers) {
  for (i = 0; i < numbersSize - 1; ++i) {

    // Find index of smallest remaining element
    indexSmallest = i;
    for (j = i + 1; j < numbersSize; ++j) {

      if (numbers[j] < numbers[indexSmallest]) {
        indexSmallest = j;
      }
    }

    // Swap numbers[i] and numbers[indexSmallest]
    temp = numbers[i];
    numbers[i] = numbers[indexSmallest];
    numbers[indexSmallest] = temp;
  }
}
