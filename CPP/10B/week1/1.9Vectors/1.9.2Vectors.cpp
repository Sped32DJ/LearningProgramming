#include <iostream>
#include <vector>
using namespace std;

int main() {
  int numDistance;
  int i;

  cin >> numDistance;
  vector<int> bikingLogs(numDistance);

  for (i = 0; i < bikingLogs.size(); ++i) {
    cin >> bikingLogs.at(i);
  }

  /* This is for even/odd indexes  */
  vector<int> vOds;
  vector<int> vEven;
  for (i = 0; i < bikingLogs.size(); ++i) {
    if (i % 2) {
      vEven.push_back(bikingLogs.at(i));
    } else {
      vOds.push_back(bikingLogs.at(i));
    }
  }

  for (i = 0; i < vOds.size(); ++i) {
    cout << vOds.at(i) << '+';
  }
  cout << endl;

  for (i = 0; i < vEven.size(); ++i) {
    cout << vEven.at(i) << '+';
  }
  cout << endl;

  return 0;
}
