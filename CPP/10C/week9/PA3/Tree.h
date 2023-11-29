#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree() : root(nullptr) {}
  ~Tree();
  void destructor(Node *);
  Tree(const Tree &cpy) : root(cpy.root) {}
  void preOrder() const { preOrder(root); }
  void inOrder() const { inOrder(root); }
  void postOrder() const { postOrder(root); }
  void insert(const string &);
  void remove(const string &);
  bool search(const string &key) const { return search(root, key); }
  bool search(Node *, const string &) const;

private:
  void preOrder(Node *) const;
  void postOrder(Node *) const;
  void inOrder(Node *) const;
  // Add additional functions/variables here
};

#endif
