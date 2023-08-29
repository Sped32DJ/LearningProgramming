#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(nullptr) {}

void IntList::push_front(int val) {
  if (!head) {
    head = new IntNode(val);
  } else {
    IntNode *temp = new IntNode(val);
    temp->next = head;
    head = temp;
  }
}

// cout a single node, global member function
// Helper local function
ostream &operator<<(ostream &out, IntNode *Node) {
  if (Node) { // (if Node != nullptr)
    out << Node->value;
    if (Node->next) { // if(Node->next != nullptr)
      out << ' ';
      out << Node->next;
    }
  }
  return out;
}

// cout a list, friend member
ostream &operator<<(ostream &out, const IntList &list) {
  out << list.head; // Calling private local member function
  return out;
}

// Has head in scope, is passed to private function (below)
bool IntList::exists(int value) const { return exists(head, value); }

// Checks if value is located in IntList
// Does all the recursing
bool IntList::exists(IntNode *curr, int value) const {
  // base cases
  if (curr == nullptr)
    return false; // does not exist
  if (curr->value == value)
    return true; // exists

  // keeps looping until it reaches a basecase
  // Iterating past every node
  // curr->next is keeping up the iterations
  return exists(curr->next, value);
}
