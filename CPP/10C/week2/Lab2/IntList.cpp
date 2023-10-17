#include "IntList.h"
#include <iostream>

// Default Const
IntList::IntList()
    : dHead(nullptr), dTail(nullptr), head(nullptr), tail(nullptr) {
  dHead = new IntNode(0);
  dTail = new IntNode(0);

  dHead->next = dTail;
  dTail->prev = dHead;
}

// Destructor
IntList::~IntList() {
  while (head) {
    pop_front();
  }
  tail = nullptr;
  head = nullptr;
  dTail = nullptr;
  dHead = nullptr;
}

// TEST
void IntList::push_front(int value) {
  IntNode *tmp = new IntNode(value);
  IntNode *prev1 = dHead;
  IntNode *next1 = dHead->next;

  // pointers to temp
  prev1->next = tmp;
  next1->prev = tmp;

  // tmp pointers
  tmp->next = next1;
  tmp->prev = prev1;
}

// TEST
void IntList::push_back(int value) {
  IntNode *tmp = new IntNode(value);
  IntNode *next1 = dTail;
  IntNode *prev1 = dTail->prev;

  prev1->next = tmp;
  next1->prev = tmp;

  tmp->prev = prev1;
  tmp->next = next1;
}

// Pop functions seem right
void IntList::pop_front() {
  if (empty()) {
    return;
  }

  IntNode *prev1 = dHead;
  IntNode *curr = dHead->next;
  IntNode *next1 = curr->next;

  prev1->next = next1;
  next1->prev = prev1;

  delete curr;
}

void IntList::pop_back() {
  if (empty()) {
    return;
  }

  IntNode *next1 = dTail;
  IntNode *curr = dTail->prev;
  IntNode *prev1 = curr->prev;

  prev1->next = next1;
  next1->prev = prev1;

  delete curr;
}

bool IntList::empty() const {
  return dHead->next == dTail && dTail->prev == dHead;
}

ostream &operator<<(ostream &out, const IntList &rhs) {
  if (rhs.empty()) {
    return out;
  }

  IntNode *curr = rhs.dHead->next;

  while (curr != rhs.dTail) {
    out << curr->value;

    // Prints all but last
    if (curr->next != rhs.dTail) {
      out << ' ';
    }

    curr = curr->next;
  }

  return out;
}

void IntList::printReverse() const {
  if (empty()) {
    return;
  }

  IntNode *curr = dTail->prev;

  // Single node
  if (curr->prev == dHead) {
    cout << curr->value;
    return;
  }

  // Multiple nodes
  while (curr != dHead) {
    cout << curr->value;
    if (curr->prev != dHead) {
      cout << ' ';
    }

    curr = curr->prev;
  }
}
