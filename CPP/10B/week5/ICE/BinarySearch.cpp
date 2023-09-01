#include <iostream>
using namespace std;

// Couldn't finish it lol
/* int search(int numbers[], int numberSize, int key, int low, int high) {
  if (high >= low) {
    mid = (high + low) / 2;
    if (numbers[mid] < key) {
      low = mid + 1;
    } else if (numbers[mid] > key) {
      high = mid - 1;
    } else {
      return mid;
    }
  }
}

int search(int numbers[], int numberSize, int key) {
  int mid;
  int low;
  int high;

  low = 0;
  high = numberSize - 1;

  int result =
      search(numbers + 1, numberSize - 1, key, low, high); // helper function

  return -1; // does not find
} */

int search(int numbers[], int numberSize, int key) {
  return bsearch(numbers, 0, numberSize - 1, key);
}

int bsearch(int numbers[], int low, int high, key) {
  int mid;
  if (high >= low) {
    mid = (high + low) / 2;
    if (numbers[mid] < key) {
      low = mid + 1;
      bsearch(numbers, mid + 1, high, key);
    } else if (numbers[mid] > key) {
      high = mid - 1;
      bsearch(numbers, low - 1, mid, key);
    }
  }
}
