#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

void Quicksort_midpoint(int numbers[], int i, int k);
void partition(int arr[], int start, int end);
int partition_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);

int middle(int a, int b, int c);
static const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) { return low + rand() % (high - low + 1); }

// Fills in the array with a bunch of random vals
void fillArrays(int arr1[], int arr2[], int arr3[]) {
  for (int i = 0; i < NUMBERS_SIZE; ++i) {
    arr1[i] = genRandInt(0, NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

int main() {
  srand(time(0)); // Every time I run, new result
  // These arrays are now full of random data
  int arr1[NUMBERS_SIZE];
  int arr2[NUMBERS_SIZE];
  int arr3[NUMBERS_SIZE];
  fillArrays(arr1, arr2, arr3);

  const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds

  // Either at, or close to the speed of median-of-three
  clock_t Start_1 = clock();
  Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
  clock_t End_1 = clock();

  int time_1 = (End_1 - Start_1) / CLOCKS_PER_MS;
  cout << "Quicksort_midpoint time:\t" << time_1 << " ms\n";

  // THE CHAMPION OF SPEED
  clock_t Start_2 = clock();
  Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
  clock_t End_2 = clock();

  int time_2 = (End_2 - Start_2) / CLOCKS_PER_MS;
  cout << "Quicksort_medianOfThree:\t" << time_2 << " ms\n";

  // Damn, InsertionSort SLOW
  clock_t Start_3 = clock();
  InsertionSort(arr3, NUMBERS_SIZE);
  clock_t End_3 = clock();
  int time_3 = (End_3 - Start_3) / CLOCKS_PER_MS;
  cout << "Insertion Sort algorithm:\t" << time_3 << " ms\n";

  return 0;
}

// this function sorts the given array in the range from i to k
// using quicksort method. In this function, pivot is the midpoint
// element (numbers[(i+k)/2]). (implementation of this function is
// given in section 21.5)
int partition_midpoint(int numbers[], int i, int k) {
  int pivot = numbers[i + (k - i) / 2]; // pivot set at midpoint

  while (1) {
    // keeps right shifting until lesser than pivot
    while (numbers[i] < pivot) {
      ++i;
    }

    // keeps left shifting until greater than pivot
    while (pivot < numbers[k]) {
      --k;
    }

    // partitioning is done
    if (i >= k) {
      break;
    }

    else {
      // swaps the elements
      std::swap(numbers[i], numbers[k]);
      ++i;
      --k;
    }
  }
  return k;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
  if (i >= k) {
    return;
  }
  int right = partition_midpoint(numbers, i, k);

  // right holds the high index
  Quicksort_midpoint(numbers, i, right);     // before partition
  Quicksort_midpoint(numbers, right + 1, k); // after partition
}

// this function utilizes different pivot selection technique in
// quicksort algorithm. The pivot is the median of the following
// three values: leftmost (numbers[i]), midpoint
// (numbers[(i+k)/2]) and rightmost (numbers[k]). You should
// modify the partition function given in section 21.5 to select
// the pivot using median-of-three technique.

// Choosing a better pivot is vital for quicksort
int middle(int a, int b, int c) {

  // Median is a if it sits down the middle
  if (a > min(b, c) && a < max(b, c)) {
    return a;
  }
  // Median B
  if (b > min(a, c) && b < max(a, c)) {
    return b;
  }

  // Median value is C
  if (c > min(a, b) && c < max(a, b)) {
    return c;
  }

  cerr << "no median found" << endl;
  return -1; // error, median not found
}

int partition_medianOfThree(int numbers[], int i, int k) {
  int midpoint = i + (k - i) / 2;
  // Chooses the pivot as the middle point
  // The pivot is consistently better
  int pivot = middle(numbers[i], numbers[midpoint], numbers[k]);

  // Partitioning process
  while (1) {
    // move left index to the right
    while (numbers[i] < pivot) {
      ++i;
    }
    // move right undex to left
    while (pivot < numbers[k]) {
      --k;
    }

    // if left and right meet or cross, partition complete!
    if (i >= k) {
      break;
    } else {
      // swap elements from left to right
      std::swap(numbers[i], numbers[k]);
      ++i;
      --k;
    }
  }
  return k;
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
  // base case, array 0-1 elements
  if (i >= k) {
    return;
  }
  // partition the aray, get index of pivot
  int j = partition_medianOfThree(numbers, i, k);

  // sorts both partitions
  Quicksort_midpoint(numbers, i, j);
  Quicksort_midpoint(numbers, j + 1, k);
}

// this function sorts the given array using,
// InsertionSort method. (implementation of
// this method is provided in section 21.3).
void InsertionSort(int numbers[], int numbersSize) {
  int i = 0;
  int j = 0;
  for (i = 1; i < numbersSize; ++i) {
    j = i;

    while (j > 0 && numbers[j] < numbers[j - 1]) {
      // swaps the vals
      std::swap(numbers[j], numbers[j - 1]);
      --j;
    }
  }
}
