#include <iostream>
#include <vector>
using namespace std;

int main() {
  int numMembers;
  int i;

  cin >> numMembers;
  vector<int> bikingListings(numMembers);

  // filling in vector
  for (i = 0; i < bikingListings.size(); ++i) {
    cin >> bikingListings.at(i);
  }

  // output at even indices; start at 0, iterate every other element
  for (i = 0; i < bikingListings.size(); i += 2) {
    cout << bikingListings.at(i) << '-';
  }
  cout << endl;

  // output at odd indices; start at 1, iterate every other element
  for (i = 1; i < bikingListings.size(); i += 2) {
    cout << bikingListings.at(i) << '-';
  }
  cout << endl;

  return 0;
}

// Exercise 3
/* int main() {
  int numMembers;
  unsigned int i;
  double averageMembers;
  int sumElementData = 0;

  cin >> numMembers;
  vector<int> runningNumbers(numMembers);

  for (i = 0; i < runningNumbers.size(); ++i) {
    cin >> runningNumbers.at(i);
    sumElementData += runningNumbers.at(i);
  }

  averageMembers = sumElementData / runningNumbers.size();

  cout << "Average: " << averageMembers << endl;
  cout << "Numbers less than average: ";

  // grab the average, then list all Numbers below average
  for (i = 0; i < runningNumbers.size(); ++i) {
    if (runningNumbers.at(i) < averageMembers) {
      cout << runningNumbers.at(i) << " ";
    }
  }

  return 0;
} */

// Exercise 2
/* int main() {
  int numEmployees;
  double firstEmployee;
  double middleEmployee;
  double lastEmployee;
  unsigned int i;

  cin >> numEmployees;
  cin >> firstEmployee;
  cin >> middleEmployee;
  cin >> lastEmployee;

  vector <double> runningRoster(numEmployees);
  runningRoster.at(0) = firstEmployee;
  runningRoster.at(numEmployees-1) = lastEmployee;
  runningRoster.at(numEmployees/2) = middleEmployee;

  for (i = 0; i < runningRoster.size(); ++i) {
    cout << runningRoster.at(i) << " ";
  }
  cout << endl;

  return 0;
} */

// Exercise 1
/* int main() {
  double distance1;
  double distance2;
  double distance3;
  double distance4;
  unsigned int i;

  cin >> distance1;
  cin >> distance2;
  cin >> distance3;
  cin >> distance4;

  vector<double> swimmingDistance(4);

  swimmingDistance.at(0) = distance4;
  swimmingDistance.at(1) = distance3;
  swimmingDistance.at(2) = distance2;
  swimmingDistance.at(3) = distance1;

  for (i = 0; i < swimmingDistance.size(); ++i) {
    cout << swimmingDistance.at(i) << " ";
  }
  cout << endl;

  return 0;
} */
