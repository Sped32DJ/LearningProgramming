#include <iostream>
#include <vector>

using namespace std;
#include "IntVector.h"

// From what it looks like
//      you make your own custom Vector class
//
int main() {
  const IntVector v1;
  IntVector();
  IntVector vNums(5, 2);
  cout << "v.at() test: " << vNums.at(0) << endl;
  cout << "v.empty() test: ";
  if (vNums.empty()) {
    cout << "Empty";
  } else {
    cout << "not empty";
  }
  cout << endl;

  cout << "Size: " << vNums.size() << endl
       << "Capacity: " << vNums.capacity() << endl;
  cout << "Front: " << vNums.front() << " Back: " << vNums.back() << endl;

  return 0;
}
