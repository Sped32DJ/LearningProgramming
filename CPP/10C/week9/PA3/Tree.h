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
  void preOrder() const { preOrder(root); }
  void inOrder() const { inOrder(root); }
  void postOrder() const { postOrder(root); }
  void insert(const string &);
  void remove(const string &);
  bool search(const string &key) const { return search(root, key); }
  /* void splitTree(const string &key, Tree &left, Tree &right); */
  void splitTree(Node *curr, const string &key);
  void setChild(Node *, const char &, Node *);

private:
  void destructor(Node *);
  Node *returnNode(const string &, Node *);

  void preOrder(Node *) const;
  void postOrder(Node *) const;
  void inOrder(Node *) const;

  // Add additional functions/variables here
  bool search(Node *, const string &) const;
  /* void insert(const string &, Node *); */
  void insert(Node *, const string &);
  void remove(Node *, const string &);
};

#endif
