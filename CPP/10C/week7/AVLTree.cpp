#include "AVLTree.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// FIX  Wrong balanceFactors are being printed
//  What may be the cause?
//  Bad insertions?
//  I believe the Balance Factor calculations are perfect

// TODO Deep copy
/* AVLTree::AVLTree(AVLTree &cpy) {} */

// TODO
/* AVLTree::~AVLTree() {} */

// AVL Stuff

// Rotations
void AVLTree::rotate(Node *curr) {
  if (getBalance(curr) == 2) {
    if (getBalance(curr->left) == -1) {
      rotateLeft(curr->left);
    }
    rotateRight(curr->left);
  } else if (getBalance(curr) == -2) {
    if (getBalance(curr->right) == 1) {
      rotateRight(curr->right);
    }
    rotateLeft(curr);
  }
}

void AVLTree::rotateLeft(Node *curr) {
  // Store the necessary nodes for rotation
  Node *RLC = curr->right->left; // Right Left Child, new root
  if (curr == nullptr || curr->right == nullptr) {
    return;
  }
  if (curr->parent != nullptr) {
    // Parent, parentchild, desiredchild
    replaceChild(curr->parent, curr, curr->right); // See how to std::swap this
  } else {
    root = curr->right;
    root->parent = nullptr;
  }

  setChild(curr->right, 'L', curr);
  setChild(curr, 'R', RLC);
}

void AVLTree::rotateRight(Node *curr) {
  // Store the necessary nodes for rotation
  Node *LRC = curr->left->right; // Left Right Child, new root

  if (curr == nullptr || curr->left == nullptr) {
    return;
  }

  // Update the parent of the current node's left child
  if (curr->parent != nullptr) {
    replaceChild(curr->parent, curr, curr->left);
  } else {
    root = curr->left;
    root->parent = nullptr;
  }

  setChild(curr->left, 'R', curr);
  setChild(curr, 'L', LRC);
}

void AVLTree::setChild(Node *parent, const char &direction, Node *child) {
  if (direction != 'L' && direction != 'R') {
    throw runtime_error("Wrong direction");
  }
  if (parent != nullptr) {
    if (direction == 'L') {
      parent->left = child;
    } else if (direction == 'R') {
      parent->right = child;
    }
  }
  if (child != nullptr) { // prevents segfaults
    child->parent = parent;
  }
}
void AVLTree::replaceChild(Node *parent, Node *parentchild,
                           Node *desiredChild) {
  if (parent == nullptr) {
    return;
  }
  if (parent->left == parentchild) {
    setChild(parent, 'L', desiredChild);
  } else if (parent->right == parentchild) {
    setChild(parent, 'R', desiredChild);
  } else {
    cout << "Nah";
  }
}
// Follows findDeepest logic
int AVLTree::heightAtNode(Node *curr) const {
  if (!curr) {
    return -1;
  }
  return max(heightAtNode(curr->left), heightAtNode(curr->right)) + 1;
}

void AVLTree::printBalanceFactors() { printBalanceFactors(root); }

void AVLTree::printBalanceFactors(Node *curr) {
  if (curr) { // prevents StackOverflow
    // Recursively travels left then print
    printBalanceFactors(curr->left);
    cout << curr->data << '(' << getBalance(curr) << ')' << ", ";
    // Recursively travels right
    printBalanceFactors(curr->right);
  }
}

void AVLTree::insert(const string &key) {
  if (root == nullptr) { // Empty Tree
    Node *newNode = new Node(key);
    root = newNode;
  } else {
    insert(key, root); // Recusrive helper
  }
}
void AVLTree::insert(const string &key, Node *curr) {
  if (curr == nullptr) {
    // Base case: Create a new node and set it as the root if the tree is empty
    Node *newNode = new Node(key);
    root = newNode;
    return;
  }

  if (key > curr->data) {
    if (curr->right == nullptr) {
      // Insert the new node on the right and perform rotations
      Node *newNode = new Node(key);
      curr->right = newNode;
      newNode->parent = curr;

      // Perform rotations after inserting the node
      while (curr) {
        rotate(curr);
        curr = curr->parent;
      }
    } else {
      // Recursively insert on the right
      insert(key, curr->right);
    }
  } else if (key < curr->data) {
    if (curr->left == nullptr) {
      // Insert the new node on the left and perform rotations
      Node *newNode = new Node(key);
      curr->left = newNode;
      newNode->parent = curr;

      // Perform rotations after inserting the node
      while (curr) {
        rotate(curr);
        curr = curr->parent;
      }
    } else {
      // Recursively insert on the left
      insert(key, curr->left);
    }
  } else {
    // Key is equal to current node's data, increment count
    curr->incrementCount();
  }
}

void AVLTree::remove(const string &key) { root = fix(root, key); }

Node *AVLTree::fix(Node *curr, const string &key) {
  if (!curr)
    return nullptr;
  else if (curr->data == key) {
    if (curr->count > 1) {
      // If count is greater than 1, just decrement and return node
      curr->decrementCount();
      return curr;
    }

    if (curr->isLeaf()) { // if leaf
      delete curr;        // Can be terminated, no issues, return null
      return nullptr;
    } else if (curr->onlyLeft()) { // Only left children
      Node *victim = curr->left;
      while (victim->right) {
        victim = victim->right; // After this loop ->right is null
      }

      curr->cloneStats(victim); // Copies data/count
      victim->count = 1;        // Flagged with 1 to be killed
      curr->left = fix(curr->left, victim->data);
      return curr;
    } else if (curr->onlyRight()) { // Only right children
      Node *victim = curr->right;
      while (victim->left) {
        victim = victim->left;
      }
      curr->cloneStats(victim);
      victim->count = 1; //  Flags it with a count of 1 to be deleted in the
                         //  recursive loop
      curr->right = fix(curr->right, victim->data);
      return curr;
    } else { // Parents, have both right and left
      Node *victim = curr->left;
      while (victim->right) {
        victim = victim->right;
      }
      curr->cloneStats(victim);
      victim->count = 1; //  Flags it with a count of 1 to be deleted in the
                         //  recursive loop
      curr->left = fix(curr->left, victim->data);
      return curr;
    }
  } else if (key < curr->data) {
    // Key is less than curr node's data, go left
    curr->left = fix(curr->left, key);
    return curr;
  } else {
    // key is greater than curr's data, go right
    curr->right = fix(curr->right, key);
    return curr;
  }
}
