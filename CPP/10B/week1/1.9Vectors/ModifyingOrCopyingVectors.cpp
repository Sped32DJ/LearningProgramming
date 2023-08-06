#include <iostream>
#include <vector>
using namespace std;

int main() {
  int numElements;
  unsigned int i;
  vector<int> numsList;

  cin >> numElements;

  numsList.resize(numElements);

  /* Your code goes here */
  int start;
  int multi;
  cin >> start >> multi;
  numsList.at(0) = start;
  numsList.at(1) = multi;

  for (i = 2; i < numsList.size(); ++i) {
    numsList.at(i) = 2 * (numsList.at(i - 2) + numsList.at(i - 1));
  }

  cout << "Sequence: ";
  for (i = 0; i < numsList.size(); ++i) {
    cout << numsList.at(i) << " ";
  }
  cout << endl;

  return 0;
}

/* #include <iostream>
#include <vector>
using namespace std;

int main() {
  int numValues;
  unsigned int i;
  vector<int> marAssetValues;
  vector<int> octAssetValues;
  vector<int> octBackup;

  cin >> numValues;

  marAssetValues.resize(numValues);
  octAssetValues.resize(numValues);

  cout << "March's asset values: ";
  for (i = 0; i < marAssetValues.size(); ++i) {
    cin >> marAssetValues.at(i);
    cout << marAssetValues.at(i) << " ";
  }
  cout << endl;

  cout << "October's asset values: ";
  for (i = 0; i < octAssetValues.size(); ++i) {
    cin >> octAssetValues.at(i);
    cout << octAssetValues.at(i) << " ";
  }
  cout << endl;

  if (marAssetValues != octAssetValues) {
    cout << "March's asset values are not the same as October's asset values."
         << endl;
    octBackup = octAssetValues;
  } else {
    cout << "March's asset values are the same as October's asset values."
         << endl;
  }

  if (octBackup.size() > 0) {
    cout << "October's backup: ";
    for (i = 0; i < octBackup.size(); ++i) {
      cout << octBackup.at(i) << " ";
    }
    cout << endl;
  } else {
    cout << "Backup not needed." << endl;
  }

  return 0;
} */
