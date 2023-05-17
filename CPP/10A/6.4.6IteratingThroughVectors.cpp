#include <iostream>
#include <vector>
using namespace std;

// Exercise 1
int main() {
  vector<int> averageMiles;
  int i;
  int numElements;

  cin >> numElements;
  // Creates a vector of size numElements and initialize all values to 0
  averageMiles.resize(numElements);

  for (i = 0; i < averageMiles.size(); ++i) {
    cin >> averageMiles.at(i);
  }

  // start at an index halfway through
  // Then iterate until reaches 0
  for (i = averageMiles.size() / 2 - 1; i >= 0; --i) {
    if (i > 0) {
      cout << averageMiles.at(i);
      cout << ", ";

    } else {
      cout << averageMiles.at(i);
    }
  }

  cout << endl;

  return 0;
}

// exercise 2
int main() {
  vector<int> averageScores;
  int i;
  int numElements;

  cin >> numElements;
  // Creates a vector of size numElements and initialize all values to 0
  averageScores.resize(numElements);

  // i = at the last index
  // Start filling in the vector halfway until you reach the end
  for (i = averageScores.size() - 1; i > averageScores.size() / 2 - 1; --i) {
    cin >> averageScores.at(i);
  }

  for (i = 0; i < averageScores.size(); ++i) {
    cout << averageScores.at(i) << " ";
  }

  return 0;
}

// Exercise 3
//
int main() {
  vector<int> averageSalary;
  unsigned int i;
  int numIn;
  int maxSum;

  cin >> numIn;
  // Creates a vector of size numIn and initialize all values to 0
  averageSalary.resize(numIn);

  for (i = 0; i < averageSalary.size(); ++i) {
    cin >> averageSalary.at(i);
  }

  maxSum = 0;
  for (i = 0; i < averageSalary.size(); ++i) {
      // keep filling up maxSum until it reaches 450 or greater
    if (maxSum <= 450) {
      maxSum += averageSalary.at(i);
    }
  }

  cout << "maxSum: " << maxSum << endl;

  return 0;
}
