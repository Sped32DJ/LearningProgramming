#include "BSTree.h"
#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Constructors
BSTree::BSTree() : root(nullptr) {}

/* BSTree::BSTree(const BSTree &cpy) {
  try {
    root = copyTree(cpy.root);
  } catch (const std::bad_alloc &e) {
    std::cerr << "Memory allocation failed to copy constructor" << endl;
  }
}

Node *BSTree::copyTree(Node *root) const {
  if (!root) { // empty tree
    return nullptr;
  }

  Node *newNode = new Node(root->getData());
  if (!newNode) {
    // Handle memory allocation failure
    throw std::bad_alloc();
  }

  // Copies stats
  newNode->setCount(root->getCount());
  newNode->setLeft(copyTree(root->getLeft()));
  newNode->setRight(copyTree(root->getRight()));

  return newNode;
} */

BSTree::~BSTree() { clear(root); }

void BSTree::clear(Node *curr) {
  if (curr) {
    clear(curr->getLeft());
    clear(curr->getRight());
    delete curr;
  }
}
void BSTree::insert(const string &newStr) {
  root = insertRecursive(root, newStr);
}

Node *BSTree::insertRecursive(Node *curr, const string &newStr) {
  if (!curr) {
    // If the current node is null, create a new node with the given string
    return new Node(newStr);
  }

  if (newStr == curr->getData()) {
    // If the string already exists, increment the count
    curr->incrementCount();
  } else if (newStr < curr->getData()) {
    // If the new string is less than the current node's data, go left
    curr->setLeft(insertRecursive(curr->getLeft(), newStr));
  } else {
    // If the new string is greater than the current node's data, go right
    curr->setRight(insertRecursive(curr->getRight(), newStr));
  }

  return curr;
}

// Printing tree using recursive helper functions
void BSTree::preOrder() const { preOrder(root); }
void BSTree::inOrder() const { inOrder(root); }
void BSTree::postOrder() const { postOrder(root); }

bool BSTree::search(const string &target) const {
  Node *curr = root;
  if (!curr) {
    return false;
  }

  // BST, left for smaller
  // Right for bigger
  // Keeps going until it is found, or leaf found is found
  while (curr != nullptr && !(curr->getData() == target)) {
    if (curr->getData() < target) {
      curr = curr->getRight();
    } else if (curr->getData() > target) {
      curr = curr->getLeft();
    }
  }

  // If target is found, curr is !nullptr
  if (curr != nullptr)
    return true;
  else
    return false; // if curr is nullptr, then return false
}

string BSTree::largest() const {
  // If root is a nullptr, then BST is empty
  if (isEmpty()) {
    return "";
  }

  Node *curr = root;

  // If tree only has a root
  if (!curr->getLeft() && !curr->getRight()) {
    return curr->getData();
  }

  // Traverse to the rightmost leaf
  while (curr->getRight()) {
    curr = curr->getRight();
  }
  return curr->getData();
}

string BSTree::smallest() const {
  if (isEmpty()) {
    return "";
  }

  Node *curr = root;

  // If tree only has a root
  if (!curr->getLeft() && !curr->getRight()) {
    return curr->getData();
  }

  // Traverse to leftmost leaf
  while (curr->getLeft()) {
    curr = curr->getLeft();
  }
  return curr->getData();
}

int BSTree::height(const string &data) const {
  if (!root) { // empty tree, just go -1
    return -1;
  }

  // Search is a bool, so steal logic
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->data == data) {
      break;
    } else if (curr->data > data) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return findDeepest(curr); // Once found, enteres recursive loop
}

// Function digs straight down and returns the value of the deepest it has
// traversed
int BSTree::findDeepest(const Node *curr) const {
  if (curr == nullptr) {
    return -1;
  }
  int LHeight = findDeepest(curr->left);
  int RHeight = findDeepest(curr->right);

  return std::max(LHeight, RHeight) + 1; // +1  because it was off by one
}

void BSTree::remove(const string &key) { root = fix(root, key); }

// Better than in-class example
Node *BSTree::fix(Node *curr, const string &key) {
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
      victim->count =
          1; //  Flags it with a count of 1 to be deleted in the recursive loop
      curr->right = fix(curr->right, victim->getData());
      return curr;
    } else { // Parents, have both right and left
      Node *victim = curr->left;
      while (victim->right) {
        victim = victim->right;
      }
      curr->cloneStats(victim);
      victim->count =
          1; //  Flags it with a count of 1 to be deleted in the recursive loop
      curr->left = fix(curr->left, victim->getData());
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
