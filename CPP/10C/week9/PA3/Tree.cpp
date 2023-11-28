#include "Tree.h"
#include <iostream>

Tree::~Tree() { destructor(root); }

void Tree::destructor(Node *curr) {
  if (!curr) {
    return;
  }
  // Since 23 trees have a left, mid, and right
  // Goes to last node and starts collapsing the stack
  destructor(curr->left);
  destructor(curr->middle);
  destructor(curr->right);

  delete curr;
}

// visit root
// Traverse left subtree
// Traverse right subtree
void Tree::preOrder(Node *curr) const {
  if (curr) {
    if (curr->countData == 1) { // if has one key
      cout << curr->small << ", ";
      preOrder(curr->left);
      preOrder(curr->right);
    } else if (curr->countData == 2) { // two keys in a node
      cout << curr->small << ", ";
    }
  }
}

// Traverse left subtree
// Traverse right subtree
// visit root
void Tree::postOrder(Node *curr) const {}

// Traverse left subtree
// visit root
// traverse right subtree
void Tree::inOrder(Node *curr) const {}
