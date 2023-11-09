#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef __TREE_H__
#define __TREE_H__
class Tree {
public:
  Tree();
  Tree(const Tree &cpy);
  Tree(Node *insRoot);
  ~Tree();

  // manipulators
  void insert(const string &);
  bool search(const string &) const;
  string largest() const;
  string smaller() const;
  int height(const string &) const;
  void remove(const string &);

  // Printing tree
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;

private:
  Node *root;

  // Printing private
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;

  Node *min(Node *curr) const;         // helper to find min
  Node *max(Node *curr) const;         // helper to find max
  void remove(Node *, Node *, string); // recursive helper function
  bool isEmpty() const;
};

#endif
