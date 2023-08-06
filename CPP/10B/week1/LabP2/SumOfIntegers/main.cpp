#include <cstdlib> //needed for exit function
#include <fstream>
#include <iostream>

using namespace std;

// Place fileSum prototype (declaration) here
int fileSum(string fileName);

int main() {

  string filename;
  int sum = 0;

  cout << "Enter the name of the input file: ";
  cin >> filename;
  cout << endl;

  sum = fileSum(filename);

  cout << "Sum: " << sum << endl;

  return 0;
}

int fileSum(string fileName) {
  ifstream inFS;

  int data;
  int sumation = 0;

  inFS.open(fileName);

  if (inFS.is_open()) {
    while (inFS >> data) {
      sumation += data;
    }
  } else {
    cout << "Error opening " << fileName << endl;
    exit(EXIT_FAILURE);
  }

  inFS.close();

  return sumation;
}
// Place fileSum implementation here
