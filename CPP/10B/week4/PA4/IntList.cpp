#include "IntList.h"
#include <iostream>

using namespace std;

// Empty list
IntList::IntList() : head(nullptr), tail(nullptr) {}

// Performs a deep copy of the item
// Current goes through the list and copies each item
IntList::IntList(const IntList &cpy) : head(nullptr), tail(nullptr) {
  IntNode *curr = cpy.head;
  /* IntList listCopy; // Implicit, not required*/
  // loops until it reaches tail
  while (curr != nullptr) {
    push_back(curr->value);
    curr = curr->next;
  }
}

// Or you can just call clear()
IntList::~IntList() {
  while (head) {
    pop_front();
  }
  tail = nullptr;
  head = nullptr;
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

  // if(empty()){ // BAD
  if (tail == nullptr) {
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

// print Space seperated int list
ostream &operator<<(ostream &out, const IntList &List) {
  IntNode *curr = List.head;
  while (curr != nullptr) {
    out << curr->value;
    if (curr->next != nullptr) {
      out << ' ';
    }
    curr = curr->next;
  }
  return out;
}

// Assignment function
// NOTE  "Make sure this makes a deep copy"
IntList &IntList::operator=(const IntList &rhs) {
  if (this != &rhs) { // & very important
    clear();

    // Grabs rhs and Implicitly copies it
    IntNode *rhsCurr = rhs.head;
    while (rhsCurr != nullptr) {
      push_back(rhsCurr->value);
      rhsCurr = rhsCurr->next;
    }
  }
  return *this; // returns the reference
}

// Reverse push_front
void IntList::push_back(int value) {
  IntNode *newtail = new IntNode(value);
  if (empty()) {
    this->tail = newtail;
    this->head = newtail;
    // NOTE  CONSTRUCTION
  } else {
    newtail->next = nullptr;
    // Makes sure tail->next and tail both points to newtail
    this->tail->next = newtail;
    this->tail = newtail;
  }
}

// NOTE  CONSTRUCTION
// Sort into Ascending order
// Nestted forloop, (nvm, we have helper functions)
// look for min, then push_back (use insert_ordered)
// Straight up deletes the nodes...
void IntList::selection_sort() {
  if (empty()) {
    return;
  }

  IntList sorted;

  // goes through implicit until empty
  while (!empty()) {
    IntNode *curr = head;
    sorted.insert_ordered(curr->value);
    pop_front();
  }

  head = sorted.head;
  tail = sorted.tail;

  sorted.head = nullptr;
  sorted.tail = nullptr;
}
// Was part of selection_sort()
/* IntList dupe(*this); // declares and dupes constructor
IntNode *curr = dupe.head;
// Implicitly clears to later fill
clear();

while (curr != nullptr) {
  // Perfect because of built in push_back
  insert_ordered(curr->value);
  curr = curr->next;
} */

// NOTE  CONSTRUCTION
// Inserts a node, and puts it in order
void IntList::insert_ordered(int value) {

  IntNode *insNode = new IntNode(value);

  // Most efficient way, single iteration
  if (empty() || value <= head->value) {
    push_front(value); // takes care of mem management
    return;
  }
  if (value >= tail->value) {
    push_back();
    return;
  }

  // If there is a value in the middle
  IntNode *prev = head;
  IntNode *curr = head->next;

  // Loops until it inserts intself
  while (curr != nullptr) {
    /* if (value > prev->value && value > prev->next) { */
    // iteratres until it finds a place to insert itself
    if (value <= curr->value) {
      prev->next = insNode;
      insNode->next = curr;
      return;
    }

    prev = curr;
    curr = curr->next;
  }

  // If insNode is the largest node
  // Least efficient to add tail
  // NOTE  Maybe redundant
  prev->next = insNode;
  tail = insNode;
}

// NOTE  PASSED
void IntList::remove_duplicates() {
  if (empty()) {
    return;
  }

  IntNode *curr = head;
  while (curr != nullptr) {
    IntNode *checker = curr;
    // nested while loop for anti-dupe check
    while (checker->next != nullptr) {
      // Looks to see if any future notes have same val
      if (checker->next->value == curr->value) {
        IntNode *dupe = checker->next;
        checker->next = checker->next->next;

        // just call deconstructor
        delete dupe;
      } else {
        checker = checker->next;
      }
    }
    // keep iterating
    curr = curr->next;
  }

  // Updating tail since back() returned wrong val
  if (head == nullptr) {
    tail = nullptr;
  } else {
    IntNode *newTail = head;
    // keep iterating until it reaches an end
    // thhen that becomes this->tail
    while (newTail->next != nullptr) {
      newTail = newTail->next;
    }
    this->tail = newTail;
  }
}
