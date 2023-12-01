#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

class AVLTree {
public:
  AVLTree() : root(nullptr) {}
  ~AVLTree();
  AVLTree(const AVLTree &cpy) = delete;

  // Insert binary tree, rotation if necessary
  void insert(const string &); // insert a node with the given string

  // Traverse and print the tree inorder rotation.
  // Print the string followed by its balance factor in parenthesis
  // followed by a , and one space
  void printBalanceFactors() ;

  // Generate dotty file and visualize tree using dotty program.
  // Call function before and after rotation
  void visualizeTree(const string &) ;

  void remove(const string &);

  int heightAtNode(Node *curr) const;

  bool search(const string &) const;
  string largest() const;
  string smallest() const;

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
  void setChild(Node *, const char &, Node *);

  // Insert helper
  void insert(const string &newStr, Node *curr);
  // remove helper
  Node *fix(Node *curr, const string &key);

  void replaceChild(Node *, Node *, Node *);

  int getBalance(Node *curr) const {
    if (!curr)
      return 0;
    return (heightAtNode(curr->left) - heightAtNode(curr->right));
  }

  int findUnbalanceNode(); // Finds + return closest unbalanced node

  void rotate(Node *); // implement 4 possible imbalance cases
                       // and update hte parent
                       // of the given node
                       // Rotate subtree to left at given node
                       // and return new subroot
  void rotateLeft(Node *);
  void rotateRight(Node *);
  void printBalanceFactors(Node *); // Rotate the subtree to left at the given
                                    // node and return new subroot

  void visualizeTree(ofstream &, Node *);
  AVLTree &operator=(const AVLTree &) = delete;
  void deleteTree(Node *); // Destructor
  bool isEmpty() const;
};
