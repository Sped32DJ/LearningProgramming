#include "minFunc.h"
const int *min(const int arr[], int arrSize) {
  // base cases, where looping ends
  if (arrSize == 0) {
    return nullptr;
  }
  if (arrSize == 1) {
    return &arr[0];
  }
  // Building the stack
  const int *minimun = min(arr + 1, arrSize - 1);
  // arr[] = {6, 4, 8, 23, 1}

  // Does not run until the stack is being deconstructed
  if (arr[0] < *minimun) {
    return &arr[0]; // arr[0] puts the current min into min
  } else {
    return minimun;
  }
}
