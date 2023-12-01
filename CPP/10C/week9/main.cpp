#include <iostream>
using namespace std;

void Quicksort_midpoint(
    int numbers[], int i,
    int k); // this function sorts the given array in the range from i to k
            // using quicksort method. In this function, pivot is the midpoint
            // element (numbers[(i+k)/2]). (implementation of this function is
            // given in section 21.5)
void Quicksort_medianOfThree(
    int numbers[], int i,
    int k); // this function utilizes different pivot selection technique in
            // quicksort algorithm. The pivot is the median of the following
            // three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2])
            // and rightmost (numbers[k]). You should modify the partition
            // function given in section 21.5 to select the pivot using
            // median-of-three technique.
void InsertionSort(
    int numbers[],
    int numbersSize); // this function sorts the given array using InsertionSort
                      // method. (implementation of this method is provided in
                      // section 21.3).

static const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) { return low + rand() % (high - low + 1); }
void fillArrays(int arr1[], int arr2[], int arr3[]) {
  for (int i = 0; i < NUMBERS_SIZE; ++i) {
    arr1[i] = genRandInt(0, NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

int main() {
  cout << "nice";
  return 0;
}

void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);
