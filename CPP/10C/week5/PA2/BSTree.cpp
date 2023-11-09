#include "BSTree.h"
#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Constructors
Tree::Tree() { root = nullptr; }

// TODO  Finish this boy
Tree::Tree(const Tree &cpy) { tree = cpy.root; }

Tree::Tree(Node *insRoot) { root = insRoot; }
Tree::~Tree() { delete root; }

// Printing tree using recursive helper functions
void Tree::preOrder() const { preOrder(root); }
void Tree::inOrder() const { inOrder(root); }
void Tree::postOrder() const { postOrder(root); }

// manipulators
void Tree::insert(const string &inString) {
  Node *inNode = new Node(inString);

  // If empty BST, terminates once job is done
  if (!root) {
    root = inNode;
    root->setLeft(nullptr);
    root->setRight(nullptr);
    return;
  }

  Node *curr = root;

  while (curr) {
    if (inNode->getData() == curr->getData()) {
      curr->setCount(curr->getCount() + 1);
      return;
    }

    if (inNode->getData() < curr->getData()) {
      if (!curr->getLeft()) {
        break;
      } else {
        curr = curr->getLeft();
      }
    }
  }
}

bool Tree::search(const string &target) const {
  Node *curr = root;

  // BST, left for smaller
  // Right for bigger
  while (curr && (curr->getData() == target)) {
    if (curr->getData() < target) {
      curr = curr->getRight();
    } else if (curr->getData() > target) {
      curr = curr->getLeft();
    }
  }

  // If target is found, curr is !nullptr
  if (!curr)
    return true;
  else
    return false; // if curr is nullptr, then return false
}

string Tree::largest() const {
  Node *curr = root;

  // If root is a nullptr, then BST is empty
  if (isEmpty()) {
    throw runtime_error("Empty BST"); // TODO  How to properly?
    return "";
  }

  // if next node is a null, then exit and return curr
  while (curr->getRight()) {
    curr = curr->getRight();
  }
  return curr->getData();
}

string Tree::smaller() const {
  Node *curr = root;

  if (isEmpty()) {
    throw runtime_error("Empty BST"); // TODO  How to properly?
    return "";
  }

  // if next node is a null, then exit and return curr
  while (curr->getLeft()) {
    curr = curr->getLeft();
  }
  return curr->getData();
}

int Tree::height(const string &data) const {
  // Throws error if data not found
  if (!search(data)) {
    throw runtime_error("String not found"); // TODO  Throw more accurate error
  }

  // Goes left or right to find data
  Node *curr = root;
  while (curr && curr->getData() != data) {
    if (curr->getData() < data) {
      curr = curr->getRight();
    } else if (curr->getData() > data) {
      curr = curr->getLeft();
    }
  }

  // TODO  better explanation
  // Nodes sent out to an expedition to
  //    left or right of tree
  Node *currLeft = root;
  Node *currRight = root;
  int countRight = 0;
  int countLeft = 0;

  // Logic required to iterate through tree
  if (curr->getLeft()) {
    currLeft = currLeft->getLeft();
    ++countLeft;
    countLeft = countLeft + height(currLeft->getData());
  }
  if (curr->getRight()) {
    currRight = currRight->getRight();
    ++countRight;
    countRight = countRight + height(currRight->getData());
  }

  // Base Statemnet for recursion
  if (countLeft >= countRight) {
    return countLeft;
  } else {
    return countRight;
  }
}

// Printing private helper
// TODO
// Visit root
// Traverse left subtree
// Traverse right subtree
void Tree::preOrder(Node *curr) const {
  if (curr) {
    cout << curr->getData() << '(' << curr->getCount() << "), ";
    preOrder(curr->getLeft());
    preOrder(curr->getRight());
  }
}

// Traverse left subtree
// visit root
// traverse the right subtree
void Tree::inOrder(Node *curr) const {
  if (curr) {
    inOrder(curr->getLeft());
    cout << curr->getData() << '(' << curr->getCount() << "), ";
    inOrder(curr->getRight());
  }
}

// Traverse left subtree
// Traverse right subtree
// visit root
void Tree::postOrder(Node *curr) const {
  if (curr) {
    postOrder(curr->getLeft());
    postOrder(curr->getRight());
    cout << curr->getData() << '(' << curr->getCount() << "), ";
  }
}

// Left-most leaf is the smallest value
Node *Tree::min(Node *curr) const {
  // Keeps going left until leaf is found
  while (curr->getLeft()) {
    curr = curr->getLeft();
  }
  return curr;
}

// Right-most leaf is the largest value
Node *Tree::max(Node *curr) const {
  // Keeps going right until leaf is found
  while (curr->getRight()) {
    curr = curr->getRight();
  }
  return curr;
}

void Tree::remove(const string &data) {
  if (isEmpty()) {
    throw runtime_error("BST is empty");
    return;
  }
  remove(nullptr, root, data);
}

void Tree::remove(Node *, Node *, string) {
  if (root == nullptr) {
    return;
  } else if ((!root->getRight() && !root->getLeft()) &&
             (root->getData() == data)) {
    delete root;
    root = nullptr;
    return;
  }
  remove(root, root, data);
}

void Tree::remove(Node *prev, Node *curr, string &data) { // recursive helper

  if (curr == nullptr) { // empty tree
    return;
  } else if (curr->getData() == data) { // found node we want to remove
    if (curr->getCount() > 1 && curr->getData() != prev->getData()) {
      curr->setCount(curr->getCount() -
                     1); // removing element that's count is >1
      return;
    }
    if (curr == root &&
        curr->getCount() > 1) { // if node that's found is root and has count >1
      curr->setCount(curr->getCount() - 1);
      return;
    } else if (!curr->getRight() &&
               !curr->getLeft()) { // if node to be removed was a leaf

      if (curr->getData() > prev->getData()) { // if it was on the right of prev
        prev->setRight(nullptr);
        delete curr;
        return;
      } else if (curr->getData() < prev->getData()) { // if on left of prev
        prev->setLeft(nullptr);
        delete curr;
        return;
      } else if (curr->getData() == prev->getData()) { // if equal to prev
        if (prev->getRight() == nullptr) { // if right is already nptr
          prev->setLeft(nullptr);          // delete left
          delete curr;
        } else if (prev->getLeft() == nullptr) { // vice versa ^
          prev->setRight(nullptr);
          delete curr;
        } else if (prev->getRight() &&
                   prev->getLeft()) { // if both right and left aren't null
          if (curr->getData() ==
              prev->getLeft()->getData()) { // if equal to left
            prev->setLeft(nullptr);
            delete curr;
          } else if (curr->getData() ==
                     prev->getRight()->getData()) { // vice versa
            prev->setRight(nullptr);
            delete curr;
          }
        }
      }
    } else if ((curr->getLeft() != nullptr && curr->getRight() != nullptr) ||
               (curr->getLeft() != nullptr &&
                curr->getRight() == nullptr)) { // if not a leaf node
      Node *temp = max(
          curr->getLeft()); // calls max to find largest from that point forward
      curr->setData(temp->getData());
      curr->setCount(temp->getCount());
      remove(curr, curr->getLeft(), curr->getData());
    } else if (!curr->getLeft() &&
               curr->getRight()) { // if left u want to find min
      Node *temp = min(curr->getRight());
      curr->setData(temp->getData());
      curr->setCount(temp->getCount());
      remove(curr, curr->getRight(), curr->getData());
    }
  } else if (curr->getData() < data) { // if node is less than root
    remove(curr, curr->getRight(), data);
  } else if (curr->getData() > data) { // greater than root
    remove(curr, curr->getLeft(), data);
  }
}

bool Tree::isEmpty() const { return !root; }
