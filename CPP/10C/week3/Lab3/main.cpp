#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// NOTE  PSEUDO CODE, I don't think this works
// TODO  Templates!!
// Learn to write a templated class
enum T {
  string,
  double,
  int
}

vector<char>
createVector() {
  int vecSize = rand() % 26;
  char c = 'a';
  vector<char> vals;
  for (int i = 0; i < vecSize; i++) {
    vals.push_back(c);
    c++;
  }
  return vals;
}

// WTF is a T datatype
void selection_sort(vector<T> vals, int index) {}
T getElement {}

int main() {

  // Part B
  srand(time(0));
  vector<char> vals = createVector();
  char curChar;
  int index;
  int numOfRuns = 10;
  while (--numOfRuns >= 0) {
    cout << "Enter a number: " << endl;
    cin >> index;
    curChar = getElement(vals, index);
    cout << "Element located at " << index << ": is " << curChar << endl;
  }
  return 0;
}
