#include <iostream>
using namespace std;

int main() {

  int index = 1;
  while (index <= 5) {
    cout << index << endl;
    index++;
  }

  if(index = 5){
      cout << "\ntest"<< endl;
  }
  cout << "\nDone with while loop" << endl;

  int nums[] = {1, 2, 5, 7, 3};
  nums[0]; // the 0th int in the array

  for (int i = 0; i <= 5; i++) {
    cout << i << ": " << nums[1] << endl;
  }
  return 0;
}
