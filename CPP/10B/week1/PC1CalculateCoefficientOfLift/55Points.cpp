#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void readData(const string &fileName, vector<double> &vData1,
              vector<double> &vData2); // done
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &vData); // done
void reorder(vector<double> &, vector<double> &);

int main(int argc, char *argv[]) {
  string fileName;
  vector<double> vData1;
  vector<double> vData2;

  fileName = argv[1]; // input is `./a.out fileName`
  readData(fileName, vData1, vData2);

  return 0;
}

void readData(const string &fileName, vector<double> &vData1,
              vector<double> &vData2) {

  ifstream inFS;
  inFS.open(fileName);
  double temp1 = -1.69; // debugging
  double temp2 = -1.69; // garbage value

  if (inFS.is_open()) {
    while (inFS >> temp1 >> temp2) {
      vData1.push_back(temp1);
      vData2.push_back(temp2);
    }
  } else {
    cout << "Error opening " << fileName << endl;
    /* return 1; */
  }

  inFS.close();
}

double interpolation(double, const vector<double> &, const vector<double> &) {
  return 45;
}

bool isOrdered(const vector<double> &vData) {
  size_t count = 0;

  for (size_t i = 0; i + 1 < vData.size();
       ++i) {                            // Doesn't iterate out of range
    if (vData.at(i) > vData.at(i + 1)) { // previous value should be lower
      ++count;
    }
  }

  if (count == 0) { // Method does not get ascending order
    return true;
  } else {
    return false;
  }
}

void reorder(vector<double> &vData1, vector<double> &vData2) { // sort LowToHigh
  size_t indexSmall = 0;
  double temp1;
  double temp2;

  for (size_t i = 0; i + 1 < vData1.size(); ++i) {
    indexSmall = i;
    for (size_t j = i + 1; j < vData1.size(); ++j) {
      indexSmall = j;
    }
    // Swapping time!
    temp1 = vData1.at(i);
    temp2 = vData2.at(i);

    // swap
    vData1.at(i) = vData1.at(indexSmall);
    vData2.at(i) = vData2.at(indexSmall);

    vData1.at(indexSmall) = temp1;
    vData2.at(indexSmall) = temp2;
  }
}

