#include <iostream>
#include <string>

class Node {
public:
  std::string data;
  int count;
  Node *left;
  Node *right;

  Node(const std::string &value)
      : data(value), count(1), left(nullptr), right(nullptr) {}
};

class BSTree {
private:
  Node *root;

  // Helper functions
  Node *insert(Node *root, const std::string &value);
  bool search(Node *root, const std::string &value) const;
  std::string findLargest(Node *root) const;
  std::string findSmallest(Node *root) const;
  int height(Node *root, const std::string &value) const;
  Node *remove(Node *root, const std::string &value);
  void printPreOrder(Node *root) const;
  void printInOrder(Node *root) const;
  void printPostOrder(Node *root) const;

public:
  BSTree() : root(nullptr) {}

  // Public member functions
  void insert(const std::string &value);
  bool search(const std::string &value) const;
  std::string largest() const;
  std::string smallest() const;
  int height(const std::string &value) const;
  void remove(const std::string &value);

  // Printing functions
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
};

// Public member function implementations
void BSTree::insert(const std::string &value) { root = insert(root, value); }

bool BSTree::search(const std::string &value) const {
  return search(root, value);
}

std::string BSTree::largest() const { return findLargest(root); }

std::string BSTree::smallest() const { return findSmallest(root); }

int BSTree::height(const std::string &value) const {
  return height(root, value);
}

void BSTree::remove(const std::string &value) { root = remove(root, value); }

// Printing function implementations
void BSTree::preOrder() const {
  printPreOrder(root);
  std::cout << std::endl;
}

void BSTree::inOrder() const {
  printInOrder(root);
  std::cout << std::endl;
}

void BSTree::postOrder() const {
  printPostOrder(root);
  std::cout << std::endl;
}

// Helper function implementations
Node *BSTree::insert(Node *root, const std::string &value) {
  if (root == nullptr) {
    return new Node(value);
  }

  if (value == root->data) {
    root->count++;
  } else if (value < root->data) {
    root->left = insert(root->left, value);
  } else {
    root->right = insert(root->right, value);
  }

  return root;
}

bool BSTree::search(Node *root, const std::string &value) const {
  if (root == nullptr) {
    return false;
  }

  if (value == root->data) {
    return true;
  } else if (value < root->data) {
    return search(root->left, value);
  } else {
    return search(root->right, value);
  }
}

std::string BSTree::findLargest(Node *root) const {
  if (root == nullptr) {
    return "";
  }

  if (root->right == nullptr) {
    return root->data;
  }

  return findLargest(root->right);
}

std::string BSTree::findSmallest(Node *root) const {
  if (root == nullptr) {
    return "";
  }

  if (root->left == nullptr) {
    return root->data;
  }

  return findSmallest(root->left);
}

int BSTree::height(Node *root, const std::string &value) const {
  if (root == nullptr) {
    return -1;
  }

  if (value == root->data) {
    // Compute the height of the current subtree
    int leftHeight = height(root->left, value);
    int rightHeight = height(root->right, value);
    return 1 + std::max(leftHeight, rightHeight);
  } else if (value < root->data) {
    return height(root->left, value);
  } else {
    return height(root->right, value);
  }
}

Node *BSTree::remove(Node *root, const std::string &value) {
  // TODO: Implement the remove function following the specified algorithm
}

void BSTree::printPreOrder(Node *root) const {
  if (root != nullptr) {
    std::cout << root->data << "(" << root->count << "), ";
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

void BSTree::printInOrder(Node *root) const {
  if (root != nullptr) {
    printInOrder(root->left);
    std::cout << root->data << "(" << root->count << "), ";
    printInOrder(root->right);
  }
}

void BSTree::printPostOrder(Node *root) const {
  if (root != nullptr) {
    printPostOrder(root->left);
    printPostOrder(root->right);
    std::cout << root->data << "(" << root->count << "), ";
  }
}

// Example usage:
int main() {
  BSTree myTree;
  myTree.insert("Hello");
  myTree.insert("World");
  myTree.insert("Hello");
  myTree.insert("Goodbye");

  myTree.preOrder();
  myTree.inOrder();
  myTree.postOrder();

  std::cout << "Largest: " << myTree.largest() << std::endl;
  std::cout << "Smallest: " << myTree.smallest() << std::endl;

  std::cout << "Height of 'World': " << myTree.height("World") << std::endl;

  myTree.remove("Hello");
  myTree.inOrder();

  return 0;
}
