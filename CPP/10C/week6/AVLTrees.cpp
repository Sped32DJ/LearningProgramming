// NOTE  Code that I wrote down from being in class
// Height and bf is always correct
// Dismisses making book keeping
// returns instantaneous bf and height
int heightAtNode(Node *curr) {
  // empty trees are -1
  if (curr == nullptr)
    return -1;

  return max(heightAtNode(curr->left), heightAtNode(curr->right) + 1;
}

int bf(Node *curr) {
  if (curr == nullptr)
    return 0;
  return heightAtNode(curr->left) - heightAtNode(curr->right);
}

// Not sure if this is AVL or BST
// Maybe the BST PA2
void remove(key) { root = fix(root, key); }

Node *fix(curr, key) {
  // basecase
  if (curr == nullptr) // same as (!curr) right?
    return nullptr;
  if (key < curr->key) {
    curr->left = fix(curr->left, key);
  } else if (key > curr->key) {
    // recursion does the verbose checking for you
    curr->right = fix(curr->right, key);
    return curr;
  }
  curr->count--;
  if (curr->count > 0)
    return curr;
  if (LEAF()) {
    delete curr;
    return nullptr;
  } else if (onlyLEFT()) {
    Node *left = curr->left;
    delete curr;
    return left; // returns the backup
  } else if (onlyRIGHT()) {
    Node *right = curr->right;
    delete curr;
    return right; // returns the backup
  } else if (BOTH) {
    Node *victim = curr->left;
    while (victim->rightl != nullptr)
      victim = victim->right;
    curr->key = victim->key;
    curr->count = victim->count;
    victim->count = 1;
    curr->left = fix(curr->left, victim->key);
    return curr;
  }
}

// What is a heap
// BST
// redblack tree
// Implications, where is biggest node
// smallest node
// Properties
// Max height
// What is a red and what is a black node
// Root node must be red
// Red nodes are spacers
