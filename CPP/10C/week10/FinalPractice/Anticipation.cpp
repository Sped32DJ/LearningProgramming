
// Two-Three B-Trees
template <Typename T> class TwoThree() {
  struct Node {}; // act like it's here

  const TwoThreeNode *contains(const BTreeNode *node, int key) {
    if (!node) {
      return nullptr;
    }

    bool foundKeyInNode = (node->A key || node->B == key);
    if (foundKeyInNode) {
      return node;
    }
    if (key < node->A) {
      return contains(node->left, key);
    }
    if (key < node->B) {
      return contains(node->middle, key);
    } else {
      return contains(node->right, key);
    }
    return nullptr;
  }
};

template <Typename T> class stack() {
private:
  T array[10];
  size_t size;

public:
  Stack() : size(0) {}

  void pop() {
    if (size == 0) {
      throw runtime_error("Empty");
    } else {
      --size;
    }
  }

  void push(cons T & val) {
    if (size >= 10) {
      throw runtime_error("stack full");
    } else {
      array[size++] = val;
    }
  }

  T top() const {
    if (size == 0) {
      throw runtime_error("Empty");
    }
    return array[size - 1];
  }
};

template <Typename T> class queue() {
private:
  T array[10];
  size_t size;

public:
  queue() : size(0) {}

  void push() {}
  void pop();
};
