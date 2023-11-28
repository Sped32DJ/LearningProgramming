#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree() : root(nullptr) {}
  ~Tree();
  Tree(const Tree &cpy) : root(cpy.root) {}
  void insert(const string &);
  void preOrder() const { preOrder(root); }
  void inOrder() const { inOrder(root); }
  void postOrder() const { postOrder(root); }
  void remove(const string &);
  bool search(const string &) const;

private:
  void preOrder(Node *) const;
  void postOrder(Node *) const;
  void inOrder(Node *) const;
  // Add additional functions/variables here
};

#endif
