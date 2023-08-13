#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void readData(const string &fileName, vector<double> &vData1,
              vector<double> &vData2); // done
double interpolation(double lift, const vector<double> &vData1,
                     const vector<double> &vData2);
bool isOrdered(const vector<double> &vData);
void reorder(vector<double> &vData1, vector<double> &vData2);

int main(int argc, char *argv[]) {
  string fileName;
  vector<double> vFlightPath; // Flight-path angles
  vector<double> vAngle; // Coefficient of lift
  double lift = -1.69;   // Found as last
  string option;

  fileName = argv[1]; // input is `./a.out fileName`
  // User input
  // if option == "yes", restart the loop
  while (cin >> lift) {
      cin >> option;
      if(option == "No" || option == "no"){
          break;
      }
      cin.ignore();
      cin.clear();
  }

  readData(fileName, vFlightPath, vAngle);

  reorder(vFlightPath, vAngle);

  // For some reason, the function spawns an error
  lift = interpolation(lift, vFlightPath, vAngle);
  if (lift != 0) {
    cout << lift << endl;
  }

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
  }

  inFS.close();
}

double interpolation(double lift, const vector<double> &vData1,
                     const vector<double> &vData2) {

  if (vData1.empty() || vData1.size() != vData2.size()) {
    /* cout << "Error: vectors are not equal in size" << endl; */
    return 0.0;
  }

  int vSize = vData2.size(); // Prevents unsigned subtration

  if (lift <= vData1.at(0)) { // if lift < [0]
    return vData2.at(0);
  }

  if (lift >= vData1.at(vSize - 1)) { // if lift > last
    return vData2.at(vSize - 1);
  }

  for (int i = 1; i < vSize; ++i) { // interpolation required!
    if (lift <= vData1.at(i)) {     // used to have .at(i-1)
      double a = vData1.at(i - 1);
      double c = vData1.at(i);
      double f_a = vData2.at(i - 1);
      double f_c = vData2.at(i);
      // Interpolation equation
      return f_a + ((lift - a) / (c - a)) * (f_c - f_a);
    }
  }

  return lift; // returns original value
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

void reorder(vector<double> &vData1,
             vector<double> &vData2) { // sort LowToHigh
  size_t indexSmall = 0;
  double temp1;
  double temp2;

  for (size_t i = 0; i + 1 < vData1.size(); ++i) {
    indexSmall = i;

    // Find index of smallest value
    for (size_t j = i + 1; j < vData1.size(); ++j) {
      if (vData1.at(j) < vData1.at(indexSmall)) {
        indexSmall = j;
      }
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
  /* cout << "Reordered!!" << endl; // Used for debugging */
}
