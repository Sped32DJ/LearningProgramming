#include <iostream>
#include <string>
#include <vector>
using namespace std;

int GetMaximumValue(const vector<int> &v) {
  unsigned int i = 0;
  int max;

  max = v.at(0);

  for (i = 1; i < v.size(); ++i) {

    if (v.at(i) > max) {

      max = v.at(i);
    }
  }

  return max;
}

// function to populate vector
void GetUserValues(vector<int> &userValues) {

  int userInput;

  // get input from user
  cin >> userInput;

  while (userInput > -10) {

    // put userInput into vector
    userValues.push_back(userInput);

    // get next input
    cin >> userInput;
  }
}

// function to determine number of times a certain number appears in vector
int GetNumOccurOfValue(const vector<int> &userValues, int val) {

  unsigned int i;
  int cnt = 0;

  for (i = 0; i < userValues.size(); ++i) {

    if (userValues.at(i) == val) {
      ++cnt;
    }
  }

  return cnt;
}

int main() {

  // Add any needed variables here
  vector<int> values;
  int max;

  /*Call the given functions to get the values from the user, get the max value
  and output the number of occurrencdes of that max value*/

  GetUserValues(values);
  max = GetMaximumValue(values);
  cout << GetNumOccurOfValue(values, max) << endl;

  return 0;
}
