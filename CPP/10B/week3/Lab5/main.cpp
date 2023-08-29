// include any standard libraries needed
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize);

//  - Passes in an array, the size of the array by reference, and the index of a
//  value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this
//  value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index);

// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no
// comma, space or newline at the end.
void display(const double array[], int arraySize);

const int ARR_CAP = 100;

int main(int argc, char *argv[]) {

  // verify file name provided on command line
  ifstream inFS;
  inFS.open(argv[1]);
  if (!inFS.is_open()) {
    cout << "Bad filename" << endl;
    return -1;
  }
  // open file and verify it opened

  // Declare an array of doubles of size ARR_CAP.
  double array[ARR_CAP];
  double dVal;
  int index; // Index being removed
  int inputSize = 0;
  // Fill the array with up to ARR_CAP doubles from the file entered at the
  // command line.
  while (inFS >> dVal) {
    array[inputSize] = dVal;
    ++inputSize;
  }

  // Call the mean function passing it this array and output the
  // value returned.
  cout << "Mean: " << setprecision(6) << mean(array, inputSize) << endl;
  // Ask the user for the index (0 to size - 1) of the value they want to
  // remove.
  cout << "Enter index of value to be removed (0 to " << inputSize - 1
       << ") :" << endl;
  cin >> index;

  /* if (index < ARR_CAP && index >= -1) {
    cout << "Invalid index size" << endl;
    return -1;
  } */

  // Call the display function to output the array.
  cout << "Before removing value: ";
  display(array, inputSize);

  // Call the remove function to remove the value at the index
  // provided by the user.
  int newArrCap = inputSize;
  remove(array, newArrCap, index);

  // Call the display function again to output the array
  // with the value removed.
  cout << "After removing value: ";
  display(array, newArrCap);
  // Call the mean function again to get the new mean
  cout << "Mean: " << setprecision(6) << mean(array, newArrCap) << endl;

  inFS.close();
  return 0;
}

double mean(const double array[], int arraySize) {
  double sum = 0.0;
  for (int i = 0; i < arraySize; ++i) {
    double temp = array[i];
    sum += temp;
  }
  return sum / arraySize;
}

void remove(double array[], int &arraySize, int index) {
  // This is smarter, no need for temp[]
  // This skips the index (remove == skip element)
  for (int i = index; i + 1 < arraySize; ++i) {
    array[i] = array[i + 1];
  }

  --arraySize;
}

void display(const double array[], int arraySize) {
  for (int i = 0; i + 1 < arraySize; ++i) {
    cout << array[i] << ", ";
  }
  cout << array[arraySize - 1];
  cout << endl;
}
