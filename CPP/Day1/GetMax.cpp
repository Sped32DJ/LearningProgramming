#include <iostream>
/* 1337 code practice
Wait, this is just for loops */
using namespace std;

int main() {

  int i, n;
  float arr[100];

  cout << "Enter total number of elements [1-100]: ";
  cin >> n;
  cout << "\n" << endl;

  /* Storing user input */
  for (i = 0; i < n; i++) {
    cout << "Enter Number " << i + 1 << " : ";
    cin >> arr[i];
  }

  /* Loop to store the largest number in arr[0] */
  for (i = 1; i < n; ++i) {
    if (arr[0] < arr[i]) arr[0] = arr[i];
  }

  cout << endl << "Largest element = " << arr[0] << endl;

  return 0;
}
