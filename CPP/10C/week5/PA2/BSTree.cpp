#include "BSTree.h"
#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Constructors
BSTree::BSTree() { root = nullptr; }

BSTree::BSTree(const BSTree &cpy) {
  try {
    root = copyTree(cpy.root);
  } catch (const std::bad_alloc &e) {
    std::cerr << "Memory allocation failed in copy constructor" << endl;
    throw; // Rethrow the exception to indicate the failure
  }
}

// FIX  I seriously give up with this, this error is messing with everything
/* Exited with return code -6 (SIGABRT).
terminate called after throwing an instance of 'std::bad_alloc' */
Node *BSTree::copyTree(Node *root) const {
  if (!root)
    return nullptr;
  Node *newNode = new Node(root->getData());
  if (!newNode) {
    // Handle memory allocation failure
    throw std::bad_alloc();
  }
  // Copy count, left, and right
  newNode->setCount(root->getCount());
  newNode->setLeft(copyTree(root->getLeft()));
  newNode->setRight(copyTree(root->getRight()));

  return newNode;
}

BSTree::BSTree(Node *insRoot) { root = insRoot; }
BSTree::~BSTree() { delete root; } // Gives less errors
/* BSTree::~BSTree() { clear(); } // properly clears */

// FIX  May depricate (not being used)
void BSTree::clear() {
  clear(root);
  root = nullptr;
}

// FIX  May depricate (not being used)
void BSTree::clear(Node *curr) {
  if (curr) {
    clear(curr->getLeft());
    clear(curr->getRight());
    delete curr;
  }
}

// Printing tree using recursive helper functions
void BSTree::preOrder() const { preOrder(root); }
void BSTree::inOrder() const { inOrder(root); }
void BSTree::postOrder() const { postOrder(root); }

void BSTree::insert(const string &data) { root = insert(root, data); }

Node *BSTree::insert(Node *root, const string &data) {
  if (root == nullptr) {
    return new Node(data); // if root, just add new node
  }

  if (data == root->getData()) {
    root->incrementCount(); // updating counter if dupe
  } else if (data < root->getData()) {
    root->setLeft(insert(root->getLeft(), data));
  } else {
    root->setRight(insert(root->getRight(), data));
  }

  return root;
}

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
    /* throw runtime_error("Empty BST, largest"); */
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
    /* throw runtime_error("Empty BST, smallest"); */
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
  if (!root) {
    return -1;
  }

  Node *curr = root;
  while (curr != nullptr && !(curr->getData() == data)) {
    if (curr->getData() < data) {
      curr = curr->getRight();
    } else if (curr->getData() > data) {
      curr = curr->getLeft();
    }
  }

  if (curr == nullptr) {
    return -1; // Node not found
  }

  int countLeft = 0;
  int countRight = 0;

  // Logic required to iterate through tree
  if (curr->getLeft() != nullptr) {
    Node *currLeft = curr->getLeft();
    countLeft++;
    countLeft += height(currLeft->getData());
  }

  if (curr->getRight() != nullptr) {
    Node *currRight = curr->getRight();
    countRight++;
    countRight += height(currRight->getData());
  }

  // Returns the larger value, post recursive
  return std::max(countLeft, countRight);
}

// Printing private helper
// TODO
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

// Left-most leaf is the smallest value
Node *BSTree::min(Node *curr) const {
  // Keeps going left until leaf is found
  while (curr->getLeft()) {
    curr = curr->getLeft();
  }
  return curr;
}

// Right-most leaf is the largest value
Node *BSTree::max(Node *curr) const {
  // Keeps going right until leaf is found
  while (curr->getRight()) {
    curr = curr->getRight();
  }
  return curr;
}

// FIX  Casuing seg fault
/* void BSTree::remove(const string &data) { remove(nullptr, root, data); }
 */
// TESTING
// This is not really doing anything
// NOTE  Depricate
/* void BSTree::remove(Node *prev, Node *curr, const string data) {
  if (curr == nullptr) {
    // Element not found
    return;
  }

  if (curr->getData() == data) {
    if (curr->getCount() > 1 && curr != root) {
      curr->decrementCount();
    } else {
      if (curr->isLeaf()) {
        // Node is a leaf
        if (prev) {
          if (curr == prev->getLeft()) {
            prev->setLeft(nullptr);
          } else {
            prev->setRight(nullptr);
          }
        } else {
          // Node is the root
          root = nullptr;
        }
        delete curr;
      } else if (curr->hasOneChild()) {
        // Node has one child
        Node *child = (curr->getLeft()) ? curr->getLeft() : curr->getRight();
        updateParentLink(prev, curr, child);
        delete curr;
      } else {
        // Node has two children
        Node *successor = min(curr->getRight());
        curr->setData(successor->getData());
        curr->setCount(successor->getCount());
        remove(curr, curr->getRight(), successor->getData());
      }
    }
  } else if (curr->getData() < data) {
    remove(curr, curr->getRight(), data);
  } else {
    remove(curr, curr->getLeft(), data);
  }
}

// Code written in class lol
// Friday
void BSTree::remove(const string &key) { root = fix(root, key); }

Node *BSTree::fix(Node *curr, const string &key) {
  int tempCount;
  // basecase
  if (curr == nullptr) // same as (!curr) right?
    return nullptr;
  if (key < curr->getData()) {
    curr->setLeft(fix(curr->getLeft(), key));
  } else if (key > curr->getData()) {
    // recursion does the verbose checking for you
    curr->setRight(fix(curr->getRight(), key));
    return curr;
  }
  tempCount = curr->getCount() - 1;
  curr->setCount(tempCount);
  if (curr->getCount() > 0)
    return curr;
  if (curr->isLeaf()) {
    delete curr;
    return nullptr;
  } else if (curr->onlyLeft()) {
    Node *left = curr->getLeft();
    delete curr;
    return left; // returns the backup
  } else if (curr->onlyRight()) {
    Node *right = curr->getRight();
    delete curr;
    return right; // returns the backup
  } else if (curr->isParent()) {
    Node *victim = curr->getLeft();
    while (victim->getRight() != nullptr) // Not sure if needs {}
      victim = victim->getRight();
    curr->setData(victim->getData());
    curr->setCount(victim->getCount());
    tempCount = 1;
    victim->setCount(tempCount);
    curr->setLeft(fix(curr->getLeft(), victim->getData()));
    return curr;
  }
  return nullptr; // NOTE Added here to compile
} */

/* void BSTree::remove(Node *prev, Node *curr, string data) {
  if (curr == nullptr) {
    return;
  } else if (curr->getData() ==
             data) { // If current node contains our target data
    // NOTE  If leaf node (null right and left)
    if (!curr->getLeft() && !curr->getRight()) {
      if (prev) {
        // update parent to null
        if (prev->getLeft() == curr) {
          prev->setLeft(nullptr);
        } else {
          prev->setRight(nullptr);
        }
        delete curr;
      } else {
        // Node is root
        delete root;
        root = nullptr;
      }
    }

    // NOTE  Node with one child

    // if only has a right child
    else if (!curr->getLeft()) {
      // Update where node only has a right child
      updateParentLink(prev, curr, curr->getRight());
      delete curr;
    }

    // Only has a left child
    else if (!curr->getRight()) {
      updateParentLink(prev, curr, curr->getLeft());
      delete curr;
    }

    // NOTE  Node has two children
    else {
      Node *sucessor = min(curr->getRight());
      curr->setData(sucessor->getData());
      remove(curr, curr->getRight(), sucessor->getData());
    }
  } else if (curr->getData() < data) { // These two statements run
    remove(curr, curr->getRight(), data);
  } else {
    remove(curr, curr->getLeft(), data);
  }
} */

// Helps bring down complexity in Remove
void BSTree::updateParentLink(Node *prev, Node *curr, Node *child) {
  if (prev) {
    // Updates parent's pointer to child
    if (prev->getLeft() == curr) {
      prev->setLeft(child);
    } else {
      prev->setRight(child);
    }
  } else {
    // Node is root
    root = child;
  }
}

bool BSTree::isEmpty() const { return !root; }

// Inclass again
// Tuesday
void remove(const string &key) { root = fix(root, key); }
Node *fix(Node *curr, const string &key) {
  if (curr == nullptr)
    return nullptr;
  if (key < curr->getData()) {
    curr->setLeft(fix(curr->getLeft(), key));
    return curr;
  }
  if (key > curr->getData()) {
    curr->decrementCount();
  } else if (key > curr->getData()) {
    curr->decrementCount();
    if (curr->getCount() > 0)
      return curr;
    if (curr->isLeaf()) {
      delete curr;
      return nullptr;
    } else if (curr->onlyLeft()) {
      victim = curr->getLeft();
      while (victim->getRight() == nullptr)
        victim = victim->getRight();
      curr->setData(victim->getData());
      curr->setCount(victim->getCount());
      victim
    }
  }
}
