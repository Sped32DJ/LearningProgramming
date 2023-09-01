#include <iostream>
#include <string>

using namespace std;

// returns true if first n values within array are in ascending order (NO
// LOOPS!!)
bool isAscending(const int arr[], int n);

int main() {

  int arr[] = {4, 7, 1, 5};
  cout << endl;
  cout << "isAscending([4, 7, 1, 5], 4) should return false" << endl;
  cout << "isAscending([4, 7, 1, 5], 4) returned "
       << (isAscending(arr, 4) ? "true" : "false") << endl;

  int arr1[] = {1, 2, 3, 4, 5};
  cout << endl;
  cout << "isAscending([1, 2, 3, 4, 5], 5) should return true" << endl;
  cout << "isAscending([1, 2, 3, 4, 5], 5) returned "
       << (isAscending(arr1, 5) ? "true" : "false") << endl;

  int arr2[] = {3, 2, 1};
  cout << endl;
  cout << "isAscending([3, 2, 1], 3) should return false" << endl;
  cout << "isAscending([3, 2, 1], 3) returned "
       << (isAscending(arr2, 3) ? "true" : "false") << endl;

  int arr3[] = {-1};
  cout << endl;
  cout << "isAscending([-1], 1) should return true" << endl;
  cout << "isAscending([-1], 1) returned "
       << (isAscending(arr3, 1) ? "true" : "false") << endl;

  int arr4[] = {1, 2, 3, 4, 5, 4};
  cout << endl;
  cout << "isAscending([1, 2, 3, 4, 5, 4], 6) should return false" << endl;
  cout << "isAscending([1, 2, 3, 4, 5, 4], 6) returned "
       << (isAscending(arr4, 6) ? "true" : "false") << endl;

  cout << endl;
  cout << "isAscending([1, 2, 3, 4, 5, 4], 5) should return true" << endl;
  cout << "isAscending([1, 2, 3, 4, 5, 4], 5) returned "
       << (isAscending(arr4, 5) ? "true" : "false") << endl;

  int arr5[] = {10, 2, 3, 4, 5};
  cout << endl;
  cout << "isAscending([10, 2, 3, 4, 5], 5) should return false" << endl;
  cout << "isAscending([10, 2, 3, 4, 5], 5) returned "
       << (isAscending(arr5, 5) ? "true" : "false") << endl;

  int arr6[] = {3, 5, 4, 2};
  cout << endl;
  cout << "isAscending([3, 5, 4, 2], 0) should return true" << endl;
  cout << "isAscending([3, 5, 4, 2], 0) returned "
       << (isAscending(arr6, 0) ? "true" : "false") << endl;

  cout << endl;

  return 0;
}

// returns true if first n values within array are in ascending order (NO
// LOOPS!!)
bool isAscending(const int arr[], int n) {
  // base case
  if (n <= 1) { // Went through the entire stack and saw
    return true;
  }
  // must be below above to prevent segfault
  // Never runs if size = 1
  // If ahead is lesser than, ends recursion and returns false
  if (arr[0] > arr[1]) { // array ahead
    return false;
  }
  // implement recursive isAscending function

  return isAscending(arr + 1, n - 1);
}
