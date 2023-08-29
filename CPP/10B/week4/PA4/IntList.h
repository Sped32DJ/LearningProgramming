#ifndef INTLIST_H
#define INTLIST_H

#include <iostream>
using namespace std;

struct IntNode {
  int value;
  IntNode *next;
  IntNode(int value) : value(value), next(nullptr) {
    IntNode *Curr = next;
    // I love implicit variables
    while (Curr != nullptr) {
      cout << Curr->value << ' ';
      Curr = Curr->next;
    }
  }
};

class IntList {
private:
  IntNode *head;
  IntNode *tail;

public:
  IntList();
  IntList(const IntList &cpy);
  ~IntList();
  void clear();
  void push_front(int value);
  void pop_front();
  bool empty() const;
  const int &front() const;
  const int &back() const;
  // Global (non-member) Friend Function
  friend ostream &operator<<(ostream &out, const IntList &List);
  // Unique to PA4
  IntList &operator=(const IntList &rhs);
  void push_back(int value);
  void selection_sort();
  void insert_ordered(int value);
  void remove_duplicates();
};

#endif
