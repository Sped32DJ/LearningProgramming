#include "IntList.h"
#include <iostream>

using namespace std;

// Empty list
IntList::IntList() : head(nullptr), tail(nullptr) {}

IntList::~IntList() {
  while (head) {
    pop_front();
  }
}

// Clears all
void IntList::clear() {
  IntNode *curr = head;
  while (curr != nullptr) {
    IntNode *next = curr->next;
    delete curr;
    curr = next;
  }
  head = nullptr;
  tail = nullptr;
}

// Add to front of linked list
void IntList::push_front(int value) {
  IntNode *tmp = new IntNode(value);
  tmp->next = this->head;
  this->head = tmp;
  if (empty()) {
    this->tail = tmp;
  }
}

// delete front
void IntList::pop_front() {
  if (head != nullptr) {
    IntNode *next = head->next;
    delete head;
    head = next;
    if (head == nullptr) {
      tail = nullptr;
    }
  }
}

bool IntList::empty() const {
  return (this->head == nullptr || this->tail == nullptr);
}

// throw out_of_range to prevent undefined behavior
const int &IntList::front() const {
  if (empty()) {
    throw out_of_range("empty list");
  } else {
    return head->value;
  }
}

const int &IntList::back() const {
  if (empty()) {
    throw out_of_range("empty list");
  } else {
    return tail->value;
  }
}

// TODO  This is like a while loop maybe
// print Space seperated int list
ostream &operator<<(ostream &out, const IntList &List) {
  IntNode *curr = List.head;
  while (curr != nullptr) {
    if (curr != List.tail) {
      out << curr->value << ' ';
    } else {
      out << curr->value;
    }
    curr = curr->next;
  }
  return out;
}
