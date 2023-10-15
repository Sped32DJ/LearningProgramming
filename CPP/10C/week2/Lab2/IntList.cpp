#include "IntList.h"
#include <iostream>

// Default Const
IntList::IntList() {
  dHead = new IntNode(0);
  dTail = new IntNode(0);

  dHead->next = dTail;
  dHead->prev = nullptr;

  dTail->prev = dHead;
  dTail->next = nullptr;
}

// Dupe List
// TODO  Shit, forgot to add prevs
IntList::IntList(const IntList &cpy) {
  dHead = new IntNode(0);
  dTail = new IntNode(0);

  dHead->next = dTail;
  dTail->prev = dHead;

  IntNode *curr = cpy.head;
  while (curr != nullptr) {
    push_back(curr->value);
    curr = curr->next;
  }
}

// Destructor
IntList::~IntList() {
  while (head) {
    pop_front();
  }
  tail = nullptr;
  head = nullptr;
}

// TODO
void IntList::push_front(int value) {
  IntNode *tmp = new IntNode(value);

  if (empty()) {
    dHead->next = tmp;
    dTail->prev = tmp;
    return;
  }
}

// TODO
void IntList::pop_front() {
  IntNode *curr = dHead->next;
  IntNode *next = curr->next;
  IntNode *prev = dHead;

  prev = next;
  next->prev = prev;
}

void IntList::push_back() {}
// TEST
bool IntList::empty() const {
  return dHead->next == dTail && dTail->prev == dHead;
}

// TEST
ostream &operator<<(ostream &out, const IntList &rhs) {
  IntNode *curr = List.head.next;
  while (curr || curr != List.tail.prev) {
    out << curr->value;
    // NOTE  I think this prints tail, not dTail
    if (curr != List.tail.prev.prev) {
      cout << ' ';
    }

    curr = curr->next;
  }

  return out;
}

// TEST
void IntList::PrintReverse() const {
  IntNode *curr = dTail->prev;
  while (curr || curr == dHead) {
    cout << curr->value;
    if (curr->prev != dHead) {
      cout << ' ';
    }

    curr = curr->prev;
  }
}
