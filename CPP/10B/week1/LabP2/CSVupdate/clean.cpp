#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

  string inputFile;
  string outputFile;
  int value;
  size_t sum = 0;
  size_t avg = 0;
  vector<int> vValues;
  string lineString;
  stringstream inSS;
  // NOTE: Make sure inFS ignores the char ','

  // Assign to inputFile value of 2nd command line argument
  // Assign to outputFile value of 3rd command line argument
  inputFile = argv[1];
  outputFile = argv[2];

  // Create input stream and open input csv file.
  ifstream inFS;
  inFS.open(inputFile);

  // Verify file opened correctly.
  // Output error message and return 1 if file stream did not open correctly.
  if (!inFS.is_open()) {
    cout << "Error opening " << inputFile << endl;
    return EXIT_FAILURE;
  }

  // Read in integers from input file to vector.
  // FIX  I don't think this is a standard
  // But, it removes commas
  getline(inFS, lineString);
  for (size_t i = 0; i < lineString.size(); ++i) {
    if (lineString.at(i) == ',') {
      lineString.at(i) = ' ';
    }
  }
  inSS.str(lineString);
  while (inSS >> value) {
    vValues.push_back(value);
  }

  // Close input stream.
  inFS.close();

  // Get integer average of all values read in.
  for (size_t i = 0; i < vValues.size(); ++i) {
    sum += vValues.at(i);
  }
  avg = sum / vValues.size();

  // Convert each value within vector to be the difference between the original
  // value and the average.
  for (size_t i = 0; i < vValues.size(); ++i) {
    vValues.at(i) -= avg;
  }

  // Create output stream and open/create output csv file.
  ofstream outFS;
  outFS.open(outputFile);

  // Verify file opened or was created correctly.
  // Output error message and return 1 if file stream did not open correctly.
  if (!outFS.is_open()) {
    cout << "Error opening " << outputFile << endl;
    return EXIT_FAILURE;
  }

  // Write converted values into ouptut csv file, each integer separated by a
  // comma.
  // Except, no comma in the very last value
  for (size_t i = 0; i < vValues.size(); ++i) {
    if (i + 1 < vValues.size()) { // Follows every iteration but the last
      outFS << vValues.at(i) << ',';
    } else {
      outFS << vValues.at(i);
    }
  }
  outFS << endl;

  // Close output stream.

  outFS.close();
  return 0;
}
