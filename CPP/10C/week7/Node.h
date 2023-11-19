#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using namespace std;

struct Node {
  string data;
  Node *parent;
  Node *left;
  Node *right;
  int count;

  Node();
  Node(const string &data);

  void incrementCount();
  void decrementCount();

  // helpers
  bool isLeaf() const;
  bool hasOneChild() const;
  bool onlyLeft() const;
  bool onlyRight() const;
  bool isParent() const;
  void cloneStats(const Node *other) {
    data = other->data;
    count = other->count;
  }
};

#endif
