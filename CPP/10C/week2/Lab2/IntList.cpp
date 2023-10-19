#include "IntList.h"
#include <iostream>

// Default Constrct
IntList::IntList()
    : dHead(nullptr), dTail(nullptr), head(nullptr), tail(nullptr) {
  dHead = new IntNode(0);
  dTail = new IntNode(0);

  dHead->next = dTail;
  dTail->prev = dHead;
}

// Copy Constrct
IntList::IntList(const IntList &cpy)
    : dHead(nullptr), dTail(nullptr), head(nullptr), tail(nullptr) {
  dHead = new IntNode(0);
  dTail = new IntNode(0);

  if (cpy.empty()) {
    return; // job here is done, an empty list was made!
  }

  IntNode *curr = cpy.dHead->next;
  while (curr) {
    push_back(curr->value);
    curr = curr->next;
  }
}

// Destructor
IntList::~IntList() {
  while (head) {
    pop_front();
  }
  dTail = nullptr;
  dHead = nullptr;
}

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
    throw runtime_error("List is empty, can't pop_front");
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
    throw runtime_error("List is empty, can't pop_back");
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
    out << "List is empty" << endl; // throwing out error
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
    throw runtime_error("Can't print empty list!");
  }

  IntNode *curr = dTail->prev;

  // Single node
  if (curr->prev == dHead) {
    cout << curr->value << endl;
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
