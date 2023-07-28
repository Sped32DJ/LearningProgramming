#include <iostream>

using namespace std;

void divisibleByThree(size_t i) {
  if (i % 15 = 0) {
    ++i;
  }
}

int main() {
  size_t mOfThree = 1000 / 3;
  size_t mOfFive = 1000 / 5;
  size_t sumOfThree = 0;
  size_t sumOfFive = 0;
  cout << "multiples of 5: " << mOfFive << endl
       << "multiples of 3: " << mOfThree << endl;

  // stop anything divisible by 15
  // Make sure to add this within the for loop, or make it into a function
  // Fuck it, function :smilling_imp:
  for (size_t i = 0; i < mOfFive; i += 5) {
    sumOfThree += i;
  }

  for (size_t i = 0; i < mOfThree; i += 3) {
    sumOfFive += i;
  }
  cout << "Sum of Three: " << sumOfThree << endl
       << "Sum of Five: " << sumOfFive << endl;

  return 0;
}
