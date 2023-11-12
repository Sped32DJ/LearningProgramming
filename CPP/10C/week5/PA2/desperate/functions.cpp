void Tree::remove(const string &data) {
  if (isEmpty()) {
    throw runtime_error("BST is empty");
    return;
  }
  remove(nullptr, root, data);
}

void Tree::remove(Node *prev, Node *curr, const string &data) {
  if (curr == nullptr) {
    return;
  } else if (curr->getData() == data) {
    // Case 1: Node with no children (Leaf Node)
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
      if (prev != nullptr) {
        // Update parent's pointer to null
        if (prev->getLeft() == curr) {
          prev->setLeft(nullptr);
        } else {
          prev->setRight(nullptr);
        }
      } else {
        // If removing the root node
        root = nullptr;
      }
      delete curr;
    }
    // Case 2: Node with one child
    else if (curr->getLeft() == nullptr) {
      // If the node has only a right child
      // Update parent's pointer to the right child
      if (prev != nullptr) {
        if (prev->getLeft() == curr) {
          prev->setLeft(curr->getRight());
        } else {
          prev->setRight(curr->getRight());
        }
      } else {
        // If removing the root node
        root = curr->getRight();
      }
      delete curr;
    } else if (curr->getRight() == nullptr) {
      // If the node has only a left child
      // Update parent's pointer to the left child
      if (prev != nullptr) {
        if (prev->getLeft() == curr) {
          prev->setLeft(curr->getLeft());
        } else {
          prev->setRight(curr->getLeft());
        }
      } else {
        // If removing the root node
        root = curr->getLeft();
      }
      delete curr;
    }
    // Case 3: Node with two children
    else {
      // Find the successor (or predecessor) node
      Node *successor =
          min(curr->getRight()); // Change to max if using predecessor
      // Copy the successor's data to the current node
      curr->setData(successor->getData());
      // Recursively remove the successor node
      remove(curr, curr->getRight(), successor->getData());
    }
  } else if (curr->getData() < data) {
    remove(curr, curr->getRight(), data);
  } else {
    remove(curr, curr->getLeft(), data);
  }
}

// Cooler
void Tree::remove(Node *prev, Node *curr, const string &data) {
  if (curr == nullptr) {
    return;
  } else if (curr->getData() == data) {
    // Handle the case where the node is a leaf
    if (!curr->getLeft() && !curr->getRight()) {
      if (prev) {
        // Update parent's pointer to null
        if (prev->getLeft() == curr) {
          prev->setLeft(nullptr);
        } else {
          prev->setRight(nullptr);
        }
        delete curr;
      } else {
        // Node is the root
        delete root;
        root = nullptr;
      }
    } else if (!curr->getLeft()) {
      // Handle the case where the node has only a right child
      updateParentLink(prev, curr, curr->getRight());
      delete curr;
    } else if (!curr->getRight()) {
      // Handle the case where the node has only a left child
      updateParentLink(prev, curr, curr->getLeft());
      delete curr;
    } else {
      // Handle the case where the node has two children
      Node *successor = min(curr->getRight());
      curr->setData(successor->getData());
      remove(curr, curr->getRight(), successor->getData());
    }
  } else if (curr->getData() < data) {
    remove(curr, curr->getRight(), data);
  } else {
    remove(curr, curr->getLeft(), data);
  }
}

void Tree::updateParentLink(Node *prev, Node *curr, Node *newChild) {
  if (prev) {
    // Update parent's pointer to newChild
    if (prev->getLeft() == curr) {
      prev->setLeft(newChild);
    } else {
      prev->setRight(newChild);
    }
  } else {
    // Node is the root
    root = newChild;
  }
}

// latest
void Tree::remove(Node *prev, Node *curr, const string &data) {
  if (curr == nullptr) {
    return;
  } else if (curr->getData() == data) {
    // Handle the case where the node is a leaf
    if (!curr->getLeft() && !curr->getRight()) {
      if (prev) {
        // Update parent's pointer to null
        if (prev->getLeft() == curr) {
          prev->setLeft(nullptr);
        } else {
          prev->setRight(nullptr);
        }
        delete curr;
      } else {
        // Node is the root
        delete root;
        root = nullptr;
      }
    } else if (!curr->getLeft()) {
      // Handle the case where the node has only a right child
      updateParentLink(prev, curr, curr->getRight());
      delete curr;
    } else if (!curr->getRight()) {
      // Handle the case where the node has only a left child
      updateParentLink(prev, curr, curr->getLeft());
      delete curr;
    } else {
      // Handle the case where the node has two children
      Node *successor = min(curr->getRight());
      curr->setData(successor->getData());
      remove(curr, curr->getRight(), successor->getData());
    }
  } else if (curr->getData() < data) {
    remove(curr, curr->getRight(), data);
  } else {
    remove(curr, curr->getLeft(), data);
  }
}

void Tree::updateParentLink(Node *prev, Node *curr, Node *newChild) {
  if (prev) {
    // Update parent's pointer to newChild
    if (prev->getLeft() == curr) {
      prev->setLeft(newChild);
    } else {
      prev->setRight(newChild);
    }
  } else {
    // Node is the root
    root = newChild;
  }
}
