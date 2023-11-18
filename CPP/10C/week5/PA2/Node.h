#ifndef __NODE_H__
#define __NODE_H__

#include "Node.h"
#include <string>

using namespace std;

// Yes, I know I should be using a struct
// But this is to show the reasoning why parts of my code have
// set and get functions
class Node {
public: // I will just make everything public at this point
  string data;
  Node *left;
  Node *right;
  int count;

  Node();
  Node(const string &data);

  // Modifiers
  void setData(const string &);
  void setLeft(Node *);
  void setRight(Node *);
  void setCount(int);
  void incrementCount();
  void decrementCount();

  // Accessers
  string getData() const;
  Node *getLeft() const;
  Node *getRight() const;
  int getCount() const;

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
