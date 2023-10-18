#include <iostream>

using namespace std;

#ifndef __INTLIST_H__
#define __INTLIST_H__

struct IntNode {
  int value;
  IntNode *prev;
  IntNode *next;
  IntNode(int value) : value(value), prev(nullptr), next(nullptr) {}
};

class IntList {
public:
  IntList();
  IntList(const IntList &cpy);
  ~IntList();
  void pop_front();
  void pop_back();
  void push_front(int value);
  void push_back(int value);
  bool empty() const;
  friend ostream &operator<<(ostream &out, const IntList &rhs);
  void printReverse() const;

private:
  IntNode *dHead;
  IntNode *dTail;
  IntNode *head;
  IntNode *tail;
};

#endif
