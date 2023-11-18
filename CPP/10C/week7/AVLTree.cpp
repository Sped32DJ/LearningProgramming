#include "AVLTree.h"
#include <iostream>
#include <string>
using namespace std;

// TODO  What more should constructor have?
AVLTree::AVLTree() : root(nullptr) {}

// TODO Deep copy
AVLTree::AVLTree(AVLTree &cpy) {}

// TODO
AVLTree::~AVLTree() {}

// AVL Stuff
void rotateLeft() {}

int balanceFactor(Node *) const {
  if (!curr) {
    return 0;
  }
  return heightAtNode(curr->left) - heightAtNode(curr->right);
}

// Follows findDeepest logic
int AVLTree::heightAtNode(Node *curr) const {
  if (!root) {
    return -1;
  }
  return max(heightAtNode(curr->left), heightAtNode(curr->right)) + 1;
}

void AVLTree::printBalanceFactors(Node *curr) {
  if (!curr)
    return 0;
  return balanceFactor(curr);
}

// TODO  Copy the BST post quality version
// Make sure the hoe is recursive
// Insesrt into binary tree, rotate if necessary
void AVLTree::insert(const string &newStr) {
  if (isEmpty()) {
    root = new Node(newStr);
    return;
  }

  Node *curr = root;
  while (true) {
    // How to control dupes? Is there counts?
    if (curr->data == newStr) {
    }

    if (newStr < curr->data) { // going left
      if (curr->left == nullptr) {
        curr->left = new Node(newStr);
        return;
      }
      curr = curr->left;
    } else { // going right
      if (curr->right == nullptr) {
        curr->right = new Node(newStr);
        return;
      }
      curr = curr->right;
    }
  }
}

// TODO  Get the QA version
// ADD required rotations
void AVLTree::remove(const string &key) { root = fix(root, key); }

// Better than in-class example
Node *AVLTree::fix(Node *curr, const string &key) {
  if (!curr)
    return nullptr;
  else if (curr->data == key) {
    if (curr->count > 1) {
      curr->decrementCount();
      return curr;
    }
    if (curr->isLeaf()) { // if leaf
      delete curr;
      return nullptr;
    } else if (curr->onlyLeft()) { // Only left children
      Node *victim = curr->left;
      while (victim->right) {
        victim = victim->right; // After this loop ->right is null
      }

      curr->cloneStats(victim);                   // Copies data/count
      victim->count = 1;                          // Flagged with 1 to be killed
      curr->left = fix(curr->left, victim->data); // TODO  WTF IS THIS DOING
      return curr;
    } else if (curr->onlyRight()) { // Only right children
      Node *victim = curr->right;
      while (victim->left) {
        victim = victim->left;
      }
      curr->cloneStats(victim);
      victim->count = 1;
      curr->right = fix(curr->right, victim->getData());
      return curr;
    } else { // Parents, have both right and left
      Node *victim = curr->left;
      while (victim->right) { // Iterates in the rightmost node TODOO (Does it
                              // actually?)
        victim = victim->right;
      }
      curr->cloneStats(victim);
      victim->count = 1;
      curr->left = fix(curr->left, victim->getData());
      return curr;
    }
  } else if (key < curr->data) {
    curr->left = fix(curr->left, key);
    return curr;
  } else {
    curr->right = fix(curr->right, key);
    return curr;
  }
}

// END of AVL stuff

void AVLTree::visualizeTree(const string &outputFilename) {
  ofstream outFS(outputFilename.c_str());
  if (!outFS.is_open()) {
    cout << "Error" << endl;
    return;
  }
  outFS << "digraph G {" << endl;
  visualizeTree(outFS, root);
  outFS << "}";
  outFS.close();
  string jpgFilename =
      outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}

void AVLTree::visualizeTree(ofstream &outFS, Node *n) {
  if (n) {
    if (n->left) {
      visualizeTree(outFS, n->left);
      outFS << n->data << " -> " << n->left->data << ";" << endl;
    }

    if (n->right) {
      visualizeTree(outFS, n->right);
      outFS << n->data << " -> " << n->right->data << ";" << endl;
    }
  }
}

// Find Extremes functions
string AVLTree::largest() const {
  if (isEmpty()) {
    return "";
  }
  Node *curr = root;

  if (curr->isLeaf()) {
    return curr->data;
  }
  while (curr->right) {
    curr = curr->right;
  }
  return curr->data;
}

string AVLTree::smallest() const {
  if (isEmpty()) {
    return "";
  }
  Node *curr = root;

  if (curr->isLeaf()) {
    return curr->data;
  }

  while (curr->left) {
    curr = curr->left;
  }
  return curr->data;
}

// Printing tree using recursive helper functions
void BSTree::preOrder() const { preOrder(root); }
void BSTree::inOrder() const { inOrder(root); }
void BSTree::postOrder() const { postOrder(root); }
// Visit root
// Traverse left subtree
// Traverse right subtree
void BSTree::preOrder(Node *curr) const {
  if (curr) {
    cout << curr->getData() << '(' << curr->getCount() << "), ";
    preOrder(curr->getLeft());
    preOrder(curr->getRight());
  }
}

// Traverse left subtree
// visit root
// traverse the right subtree
void BSTree::inOrder(Node *curr) const {
  if (curr) {
    inOrder(curr->getLeft());
    cout << curr->getData() << '(' << curr->getCount() << "), ";
    inOrder(curr->getRight());
  }
}

// Traverse left subtree
// Traverse right subtree
// visit root
void BSTree::postOrder(Node *curr) const {
  if (curr) {
    postOrder(curr->getLeft());
    postOrder(curr->getRight());
    cout << curr->getData() << '(' << curr->getCount() << "), ";
  }
}

bool BSTree::isEmpty() const { return !root; }
