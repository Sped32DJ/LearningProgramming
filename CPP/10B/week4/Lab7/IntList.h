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
  ~IntList();
  void clear();
  void push_front(int value);
  void pop_front();
  bool empty() const;
  const int &front() const;
  const int &back() const;
  friend ostream &operator<<(ostream &out, const IntList &List);
};

#endif
