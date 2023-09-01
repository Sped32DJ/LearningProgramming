#include "IntList.h"

bool IntList::bubbleUp() {
  // if empty, recursion ends
  if (this->head == nullptr || head->next == nullptr) {
    return false;
  }

  return bubbleUp(head);
}

bool IntList::bubbleUp(IntNode *curr) {
  // returned to the end of the list
  // base case
  if (curr->next == nullptr) {
    return false;
  }

  bool swapped = false;

  // Recursively calls func to the next node
  // self call + iterative step
  // Keeps going until false (empty)
  if (bubbleUp(curr->next)) {
    swapped = true;
  }

  // Swaps values if required
  // If curr val greater than next val, SWAP
  // values smaller than the value that comes b4 it such that the smallest
  // value in the list will end up at the front of the list.
  if (curr->value > curr->next->value) {
    swap(curr->value, curr->next->value);
    swapped = true;
  }

  // Returns if any swapped happened during this loop
  return swapped;
}
