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
  if (Node) {
    out << Node->value;
    if (Node->next) {
      out << ' ';
      out << Node->next;
    }
  }
  return out;
}

// cout a list, friend member
ostream &operator<<(ostream &out, const IntList &list) {
  out << list.head;
  return out;
}

bool IntList::exists(int value) const { return exists(head, value); }

// Checks if value is located in IntList
bool IntList::exists(IntNode *curr, int value) const {
  if (curr == nullptr)
    return false;
  if (curr->value == value)
    return true;
  return exists(curr->next, value);
}
