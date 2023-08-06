#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream inFS;
  string sofaFileName;
  string purchaserName;
  int sofaQuantity;

  cin >> sofaFileName;

  inFS.open(sofaFileName);
  if (!inFS.is_open()) {
    cout << sofaFileName << ": file could not be opened" << endl;
    return 1;
  }

  /* Your code goes here */
  while (!inFS.eof()) {
    inFS >> purchaserName >> sofaQuantity;
    cout << purchaserName << " ordered " << sofaQuantity << " sofas." << endl;
  }

  inFS.close();

  return 0;
}

/* #include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream dataFS;
  string fileName;
  int shelfCount;
  int unsoldShelves;

  cin >> fileName;

  dataFS.open(fileName);
  if (!dataFS.is_open()) {
    cout << fileName << ": error occurred while opening file" << endl;
    return 1;
  }

  unsoldShelves = 360;

  cout << "Started with: " << unsoldShelves << endl;

  int value = 0;
  while (dataFS >> value) {
    cout << value << endl;
    unsoldShelves -= value;
  }


  if (dataFS.eof()) {
    cout << "Reached end of file" << endl;
  } else {
    cout << "Read failure occurred!" << endl;
  }
  cout << "Remaining: " << unsoldShelves << endl;

  dataFS.close();

  return 0;
} */

/* #include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

int main() {
  ifstream dataFS;
  string fileName;
  int sofaQuantity;
  int totalSofaCount;

  cin >> fileName;

  dataFS.open(fileName);
  if (!dataFS.is_open()) {
    cout << fileName << ": open operation failed" << endl;
    return 1;
  }

  totalSofaCount = 5;

  cout << "Started with: " << totalSofaCount << endl;

  dataFS >> sofaQuantity;
  while (!dataFS.fail()) {
    cout << sofaQuantity << endl;
    totalSofaCount = totalSofaCount + sofaQuantity;
    dataFS >> sofaQuantity;
  }

  if (dataFS.eof()) {
    cout << "File may contain bad values" << endl;
  }
  cout << "Sum: " << totalSofaCount << endl;

  dataFS.close();

  return 0;
} */
