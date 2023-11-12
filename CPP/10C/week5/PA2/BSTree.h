#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef __BSTREE_H__
#define __BSTREE_H__
class BSTree {
public:
  BSTree();
  BSTree(const BSTree &cpy);
  BSTree(Node *insRoot);
  ~BSTree();

  // manipulators
  void insert(const string &);
  bool search(const string &) const;
  string largest() const;
  string smallest() const;
  int height(const string &) const;
  void remove(const string &);
  void clear();

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

  void clear(Node *); // clears the tree
  Node *copyTree(Node *) const;
  // These helpers were used for recursion
  Node *insert(Node *, const string &);
  void updateParentLink(Node *, Node *, Node *);  // Helper for remove()
  int heightHelper(Node *, const string &) const; // Helper for Height()
  Node *min(Node *curr) const;                    // helper to find min
  Node *max(Node *curr) const;                    // helper to find max
  void remove(Node *prev, Node *curr, string data);
  int height(Node *, const string &) const;
  bool isEmpty() const;
};

#endif
