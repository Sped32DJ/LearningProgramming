#include <iostream>
#include <vector>
using namespace std;

int main() {
  int numInputs;
  int sumOdds;
  unsigned int i;

  cin >> numInputs;

  // Creates a vector of size numInputs and initializes all values to 0
  vector<int> dailyTemps(numInputs);

  for (i = 0; i < dailyTemps.size(); ++i) {
    cin >> dailyTemps.at(i);
  }

  sumOdds = 0;
  for (i = 0; i < dailyTemps.size(); ++i) {
    if (dailyTemps.at(i) % 2) { // Finds odd numbers
      sumOdds += dailyTemps.at(i);
    }
  }

  cout << "Odd sum: " << sumOdds << endl;

  return 0;
}

/* #include <iostream>
#include <vector>
using namespace std;

int main() {
  int numIn;
  unsigned int i;

  cin >> numIn;

  // Creates a vector of size numIn and initializes all values to 0
  vector<int> yearlyPrices(numIn);

  for (i = 0; i < yearlyPrices.size()/2;++i){
      cin >> yearlyPrices.at(i);
  }

  cout << endl;

  for (i = 0; i < yearlyPrices.size(); ++i) {
    cout << yearlyPrices.at(i) << " ";
  }

  return 0;
} */

/* #include <iostream>
#include <vector>
using namespace std;

int main() {
  int numIn;
  int i;

  cin >> numIn;

  // Creates a vector of size numIn and initializes all values to 0
  vector<int> averageSalary(numIn);

  for (i = 0; i < averageSalary.size(); ++i) {
    cin >> averageSalary.at(i);
  }

  for (i = averageSalary.size() / 2 - 1; i >= 0; --i) {
    if (i > 0) {
      cout << averageSalary.at(i) << ", ";
    } else {
      cout << averageSalary.at(i);
    }
  }

  cout << endl;

  return 0;
} */
