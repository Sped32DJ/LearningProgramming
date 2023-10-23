#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Part One:
template <typename T> unsigned min_index(const vector<T> &vals, unsigned index);

template <typename T> void selection_sort(vector<T> &vals);

template <typename T> T getElement(vector<T> vals, int index) {
  return vals.at(index);
}

vector<char> createVector();

// Part B
int main() {
  srand(time(0));
  vector<char> vals = createVector();
  char curChar;
  int index;
  int numOfRuns = 10;
  while (--numOfRuns >= 0) {
    try {
      cout << "Enter a number: " << endl;
      cin >> index;
      if (cin.fail()) {
        throw runtime_error("Bad input index");
      }
      curChar = getElement(vals, index); // .at() will throw an out_of_range
      cout << "Element located at " << index << ": is " << curChar << endl;
    } catch (const std::out_of_range &excpt) {
      cout << excpt.what() << endl;
      cout << "out of range exception occured" << endl;
    }
  }

  return 0;
}

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
  T minVal = vals.at(index); // Must initialize with index
  unsigned minIn = index;

  for (size_t i = index + 1; i < vals.size(); ++i) {
    if (minVal > vals.at(i)) {
      minVal = vals.at(i);
      minIn = i;
    }
  }
  return minIn;
}

template <typename T> void selection_sort(vector<T> &vals) {
  for (size_t i = 0; i < vals.size(); ++i) {
    unsigned minIn = min_index(vals, i);
    swap(vals.at(i), vals.at(minIn)); // no need for nested loop
  }
}

vector<char> createVector() {
  int vecSize = rand() % 26;
  char c = 'a';
  vector<char> vals;
  for (int i = 0; i < vecSize; ++i) {
    vals.push_back(c);
    ++c;
  }
  return vals;
}
