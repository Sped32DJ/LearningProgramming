#include "Heap.h"
#include <iostream>

Heap::Heap() : numItems(0) {}

Heap::Heap(const Heap &cpy) : numItems(cpy.numItems) {
  for (int i = 0; i < numItems; ++i) {
    arr[i] = new PrintJob(*cpy.arr[i]);
  }
}

Heap::~Heap() {
  for (int i = 0; i < numItems; ++i) {
    delete arr[i]; // Deletes very PrintJob pointers
  }
}

void Heap::enqueue(PrintJob *newJob) {
  if (isFull()) {
    arr[numItems] = newJob; // inserting the newJob to array
    ++numItems;

    // bubble up to keep max head property
    int curr = numItems - 1;
    while (curr > 0 &&
           arr[curr]->getPriority() > arr[(curr - 1) / 2]->getPriority()) {
      std::swap(arr[curr], arr[(curr - 1) / 2]);
      curr = (curr - 1) / 2;
    }
  }
}

// Returns node with highest priority (top of the heap)
PrintJob *Heap::highest() {
  if (numItems > 0) {
    return arr[0]; // highest priorty is stored at the root in max-heap
  } else {
    return nullptr;
  }
}

void Heap::dequeue() {
  if (numItems > 0) {
    // Swap root with last elements
    std::swap(arr[0], arr[numItems - 1]);

    // decrement numitems
    --numItems;

    // trickleDown on the root to keep max-heap property
    trickleDown(0);
  }
}

// Prints the PrintJob with highest priority in given format
void Heap::print() {
  cout << "Priority: " << arr[0]->getPriority() << ", ";
  cout << "Job Number: " << arr[0]->getJobNumber() << ", ";
  cout << "Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int index) {
  int leftIndex = 2 * index + 1;
  int rightIndex = 2 * index + 2;
  int largestIndex = index;

  // Checks if left parents has higher priority compared to curr child
  // If priority does not respect max-heap property
  //    Largest index is collected to later make a swap
  if (leftIndex < numItems &&
      arr[leftIndex]->getPriority() > arr[largestIndex]->getPriority()) {
    largestIndex = leftIndex;
  }
  if (rightIndex < numItems &&
      arr[rightIndex]->getPriority() > arr[largestIndex]->getPriority()) {
    largestIndex = rightIndex;
  }

  // Recursive calls until index and largest index are equal
  // Meaning, no more swaps are required in the trickle process
  // Keeps max-heap property
  if (largestIndex != index) {
    std::swap(arr[index], arr[largestIndex]);
    trickleDown(largestIndex); // recursive call
  }
}

// Useful to see if full or empty
bool Heap::isFull() const { return numItems < MAX_HEAP_SIZE; }
bool Heap::isEmpty() const { return numItems > 0; }
