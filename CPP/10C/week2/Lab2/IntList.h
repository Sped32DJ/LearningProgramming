using namespace std;

#ifndef __INTLIST_H__
#define __INTLIST_H__

struct IntNode {
  int data;
  IntNode *prev;
  IntNode *next;
  IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList() {
public:
  IntList();
  ~IntList();
  void push_front(int value);
  void pop_front();
  void push_back();
  bool empty() const;
  friend ostream &operator<<(ostream &out, const IntList &rhs);
  void PrintReverse() const;

private:
  IntNode *dHead;
  IntNode *dTail;
  IntNode *head;
  IntNode *tail;
};

#endif
