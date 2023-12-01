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
      preOrder(curr->left);
      cout << curr->large << ", ";
      preOrder(curr->middle);
      preOrder(curr->right);
    }
  }
}

// Traverse left subtree
// Traverse right subtree
// visit root
void Tree::postOrder(Node *curr) const {
  if (curr) {
    if (curr->countData == 1) { // One key
      postOrder(curr->left);
      postOrder(curr->right);
      cout << curr->small << ", ";
    } else if (curr->countData == 2) { // two keys
      postOrder(curr->left);
      postOrder(curr->middle);
      cout << curr->small << ", ";
      postOrder(curr->right);
      cout << curr->large << ", ";
    }
  }
}

// Traverse left subtree
// visit root
// traverse right subtree
void Tree::inOrder(Node *curr) const {
  if (curr) {
    if (curr->countData == 1) { // one key
      inOrder(curr->left);
      cout << curr->small << ", ";
      inOrder(curr->right);
    } else if (curr->countData == 2) { // two keys
      inOrder(curr->left);
      cout << curr->small << ", ";
      inOrder(curr->middle);
      cout << curr->large << ", ";
      inOrder(curr->right);
    }
  }
}

bool Tree::search(Node *curr, const string &key) const {
  if (curr) {
    if (curr->small == key || curr->large == key) { // base case
      return true;
    } else {
      // Order of the if statements
      // Traverse left tree
      // Traverse middle tree
      // Traverse Right Tree
      if (key < curr->small)
        return search(curr->left, key);
      else if (curr->countData == 2 &&
               key < curr->large) // Check if middle && check key in middle node
        return search(curr->middle, key);
      else
        return search(curr->right, key);
    }
  }
  return false; // If never found
}

void Tree::insert(const string &key) {
  if (root) {
    insert(root, key);
  } else {
    Node *newNode = new Node(key);
    root = newNode;
  }
}

void Tree::insert(const string &key, Node *curr) {
  if (!curr) { // base case, curr == null
    return;
  }
  if (key < curr->small) { // Key smaller than both keys

    if (curr->countData == 1) {
      if (curr->left == nullptr) {
        curr->large = curr->small;
        curr->small = key;
        ++curr->countData;
      }
      insert(key, curr->left);
    } else if (curr->countData == 2) {
      insert(key, curr->left);
    }

  } else if (key > curr->small) { // Key between or bigger than curr
  }
}

void Tree::remove(const string &key) { return; }
