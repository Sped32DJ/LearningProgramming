#include <iostream>
using namespace std;

int main() {
  bool sun;
  int Age, Price;
  string timeOfDay;

  cin >> timeOfDay >> Age;

  if (timeOfDay == "day") {
    sun = true;
  }

  if (sun) {
    if (Age < 4) {
      Price = 0;
    } else {
      Price = 8;
    }
  } else {
    if (Age < 4) {
      Price = 0;
    } else if (Age >= 4 && Age <= 16) {
      Price = 12;
    } else if (Age >= 17 && Age <= 54) {
      Price = 15;
    } else if (Age >= 55) {
      Price = 13;
    }
  }

  if (Price == 0) {
    cout << "free";
  } else {
    cout << '$' << Price;
  }
  cout << endl;

  // Age < 4 // kid, free price
  // Day, $8, Age >= 4
  // Night, Age (4-16) = $12
  //      Age(17-54) = $15
  //      Age (55+) = $13
  return 0;
}
