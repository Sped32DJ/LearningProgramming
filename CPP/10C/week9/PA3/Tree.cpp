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

void Tree::splitTree(Node *curr, const string &key) {
  // left child, right child, middle child
  Node *lc = nullptr;
  Node *rc = nullptr;
  string mc;

  if (curr->large == "") { // base case
    return;
  }

  if (key == curr->small || key == curr->large) { // If dupe
    throw runtime_error("dupe");
  }

  if (key < curr->small) {
    lc = new Node(key);
    mc = curr->small;
    rc = new Node(curr->large);
  } else if (key > curr->large) {
    lc = new Node(curr->small);
    mc = curr->large;
    rc = new Node(key);
  } else {
    lc = new Node(curr->small);
    mc = key;
    rc = new Node(curr->large);
  }
  curr->large = "";
  --curr->countData;

  if (curr->parent != nullptr) {
    curr->parent->large = mc;
    ++curr->parent->countData;

    curr->parent->middle = lc;
    lc->parent = curr->parent;
    /* setChild(curr->parent, 'M', lc); */

    curr->parent->right = rc;
    rc->parent = curr->parent;
    /* setChild(curr->parent, 'R', rc); */
  } else {
    curr->small = mc;

    curr->left = lc;
    curr->right = rc;

    lc->parent = curr;
    rc->parent = curr;
    /* setChild(curr, 'L', lc);
    setChild(curr, 'R', rc); */
  }
}

void Tree::setChild(Node *brother, const char &direction, Node *child) {
  if (direction != 'L' && direction != 'R' &&
      direction != 'M') { // shouldn't run since it is private
    throw runtime_error("Invalid direction");
  }

  // Check every node before using it
  if (brother != nullptr) {
    if (direction == 'L') {
      brother->left = child;
    } else if (direction == 'R') {
      brother->right = child;
    } else if (direction == 'M') {
      brother->middle = child;
    }
  }

  // Share parent
  if (child != nullptr) {
    child->parent = brother->parent;
  }
}

void Tree::insert(Node *curr, const string &key) {
  if (!curr) { // base case, curr == null
    return;
  }
  if (key < curr->small) { // Key smaller than both keys

    if (curr->countData == 1) {
      if (curr->left == nullptr) { // Left is null so insert
        curr->large = curr->small;
        curr->small = key;
        ++curr->countData;
      } else
        insert(curr->left, key);

    } else if (curr->countData == 2) {
      if (curr->left != nullptr)
        insert(curr->left, key);
      else
        splitTree(curr, key);
    } else {
      splitTree(curr, key);
    }

  } else if (key > curr->small) { // Key between or bigger than curr
    if (curr->countData == 1) {
      if (curr->right == nullptr) {
        curr->large = key;
        ++curr->countData;
      } else {
        insert(curr->right, key);
      }
    } else if (curr->countData == 2 && key < curr->large) {
      if (curr->middle != nullptr) {
        insert(curr->middle, key);
      } else
        splitTree(curr, key);
    } else
      splitTree(curr, key);
  }
}

void Tree::remove(const string &key) { remove(key, root); }

void Tree::remove(const string &key, Node *curr) {
  if (curr == nullptr)
    return;
  if (search(key, curr)) {
    curr = returnNode(key, curr);

    if (curr->parent == nullptr) {
      if (curr->parent == nullptr) {
      }
    }
  }
}

Node *Tree::returnNode(const string &key, Node *curr) {
  if (!curr)
    return nullptr;
  if (curr->small == key || curr->large == key)
    return curr;
  else {
    if (key < curr->small) {
      return returnNode(key, curr->left);
    } else if (curr->countData == 2 && key < curr->large) {
      return returnNode(key, curr->middle);
    } else
      return returnNode(key, curr->right);
  }
}
