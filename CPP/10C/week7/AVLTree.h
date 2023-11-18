#include <iostream>
#include <string>

using namespace std;

class AVLTree {
public:
  AVLTree();
  ~AVLTree();
  AVLTree(const AVLTree &cpy) = delete;

  // Insert binary tree, rotation if necessary
  void insert(const string &);
  // Returns the balance factor of given node
  int balanceFactor(Node *) const;
  // Traverse and print the tree inorder rotation.
  // Print the string followed by its balance factor in parenthesis
  // followed by a , and one space
  void printBalanceFactors();
  // Generate dotty file and visualize tree using dotty program.
  // Call function before and after rotation
  void visualizeTree(const string &);

  void remove();

  void height() const;

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

  void findUnbalanceNode(); // Finds + return closest unbalanced node
  void rotate(); // implement 4 possible imbalance cases and update hte parent
                 // of the given node
  void
  rotateLeft(); // Rotate subtree to left at given node and return new subroot
  void printBalanceFactors(Node *); // Rotate the subtree to left at the given
                                    // node and return new subroot

  void visualizeTree(ofstream &, Node *);
  AVLTree &operator=(const AVLTree &); // Overloaded assignment operator
  bool isEmpty() const;
};
