#include <iostream>

const size_t MAX_SIZE = 1000; // Maximum size of the array

size_t *findLaterDuplicates(const int array[], size_t size) {
  size_t *laterDuplicates = new size_t[size];
  for (size_t i = 0; i < size; ++i) {
    laterDuplicates[i] = 0; // Initialize all elements to 0
  }

  int indexMap[MAX_SIZE] = {0}; // Initialize all elements to 0

  size_t nextIndex =
      1; // Keep track of the next available index in laterDuplicates

  for (size_t i = 0; i < size; ++i) {
    int value = array[i];
    if (indexMap[value] != 0) {
      laterDuplicates[indexMap[value] - 1] = i;
    } else {
      indexMap[value] = nextIndex;
      ++nextIndex;
    }
  }

  return laterDuplicates;
}

int main() {
  int array[] = {1, 2, 3, 2, 5, 1, 6, 7, 5, 5, 8, 8, 3};
  size_t size = sizeof(array) / sizeof(array[0]);

  size_t *laterDuplicateIndices = findLaterDuplicates(array, size);

  for (size_t i = 0; i < size; ++i) {
    if (laterDuplicateIndices[i] != 0) {
      std::cout << "Later duplicate found at index: "
                << laterDuplicateIndices[i] << std::endl;
    }
  }
  std::cout << "Size: " << size << std::endl;

  delete[] laterDuplicateIndices;

  return 0;
}
