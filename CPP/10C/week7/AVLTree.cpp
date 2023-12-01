#include "AVLTree.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Constructor in AVLTree.h

AVLTree::~AVLTree() { deleteTree(root); }
void AVLTree::deleteTree(Node *node) {
  if (node == NULL) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

// AVL Stuff

// Rotations
void AVLTree::rotate(Node *curr) {
  if (getBalance(curr) == 2) {          // unbalanced left
    if (getBalance(curr->left) == -1) { // Double rotate edge case
      rotateLeft(curr->left);
    }
    rotateRight(curr);

  } else if (getBalance(curr) == -2) {  // unbalanced right
    if (getBalance(curr->right) == 1) { // Double rotate edge case
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
    // Format: Parent, parentchild, desiredchild
    replaceChild(curr->parent, curr, curr->right);
  } else {
    root = curr->right;
    root->parent = nullptr;
  }

  // Helper sets children && update parent
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
    // Format: Parent, parentchild, desiredchild
    replaceChild(curr->parent, curr, curr->left);
  } else {
    root = curr->left;
    root->parent = nullptr;
  }

  setChild(curr->left, 'R', curr); // curr->left->right = curr
  setChild(curr, 'L', LRC);        // curr->left = LRC
}

// Sets children and updates parent
void AVLTree::setChild(Node *parent, const char &direction, Node *child) {
  if (direction != 'L' &&
      direction != 'R') { // shouldn't run since it is private
    throw runtime_error("Invalid direction");
  }

  // Check every node before using it
  if (parent != nullptr) {
    if (direction == 'L') {
      parent->left = child;
    } else if (direction == 'R') {
      parent->right = child;
    }
  }

  // Updates the parent
  if (child != nullptr) {
    child->parent = parent;
  }
}

// Cleaner syntax and no messing with pointers
// Helps with rotations
void AVLTree::replaceChild(Node *parent, Node *parentchild, Node *newChild) {
  if (!parent) { // no parent ;(
    return;
  }

  if (parent->left == parentchild) { // For left rotation
    setChild(parent, 'L', newChild);
  } else if (parent->right == parentchild) { // For Right rotation
    setChild(parent, 'R', newChild);
  } else {
    cout << "Invalid" << endl;
  }
}

// Follows findDeepest logic
int AVLTree::heightAtNode(Node *curr) const {
  if (!curr) {
    return -1;
  }
  // Recursively digs down
  // getBalance() uses this function and is defined in AVLTree.h
  return max(heightAtNode(curr->left), heightAtNode(curr->right)) + 1;
}

void AVLTree::printBalanceFactors() { printBalanceFactors(root); }

// Private Helper
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
      // Recursively insert on the left until finds where key should be placed
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
