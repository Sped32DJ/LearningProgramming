#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef __BSTREE_H__
#define __BSTREE_H__
class BSTree {
public:
  BSTree();
  ~BSTree();

  // manipulators
  void insert(const string &);       // G
  bool search(const string &) const; // G
  string largest() const;            // G
  string smallest() const;           // G
  int height(const string &) const;  // G
  void remove(const string &);       // G

  // Printing tree
  void preOrder() const;  // G
  void inOrder() const;   // G
  void postOrder() const; // G

private:
  Node *root;

  // Printing private
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;

  void clear(Node *); // clears the tree
  Node *copyTree(Node *) const;

  // These helpers were used for recursion
  Node *fix(Node *, const string &);    // Helper for remove
  Node *insert(Node *, const string &); // Helper for insert
  int findDeepest(const Node *) const;  // Helper Height
  bool isEmpty() const;

  BSTree &operator=(const BSTree &) = delete;
  BSTree(const BSTree &copy) = delete;
};

#endif
