#include <iostream>
using namespace std;

int main() {
  int numRows;
  int numColumns;
  int currentRow;
  int currentColumn;
  int currentColumnInteger;

  cin >> numRows;
  cin >> numColumns;

  for (size_t i = 1; i <= numRows; ++i) {
    for (size_t j = 1; j <= numColumns; ++j) {
      cout << i << j << ' ';
    }
  }

  cout << endl;

  return 0;
}

/* int main() {
  int firstNum;
  int secondNum;
  int i;
  int j;

  cin >> firstNum;
  cin >> secondNum;

  // Rows, inclusive range
  // Then Columns
  for (i = 0; i < secondNum - firstNum + 1; ++i) {
    for (j = 0; j < firstNum + i; ++j) {
      cout << '-';
    }
    cout << endl;
  }

  return 0;
} */
