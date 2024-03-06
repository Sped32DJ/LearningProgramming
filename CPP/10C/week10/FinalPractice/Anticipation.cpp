
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

// Doing Queue again!
template <typename T> class Queue {
private:
  struct Node {
    T value;
    Node *next;
    Node(const T &v) : value(v), next(nullptr) {}
  };
  unsigned maxSize;
  Node *head;
  Node *tail;
  unsigned length;

public:
  Queue(unsigned maxSize)
      : maxSize(maxSize), head(nullptr), tail(nullptr), length(0) {}
  void enqueue(const T &x) {
    if (length == maxSize) {
      throw runtime_error("overflow");
    }
    Node *n = new Node(x);
    if (!tail) {
      head = tail = n;
    } else {
      n->next = head;
      head = n;
    }
    length++;
  }
  void dequeue() {
    if (isEmpty()) {
      throw runtime_error("underflow");
    }
    Node *victim = head;
    head = head->next;
    delete victim;
    --length;
    if (length == 0)
      tail = nullptr; // Fix tail on empty
  }
  const T &peek() const { // May not return a Node*! Read Q!
    if (isEmpty()) {
      throw runtime_error("underflow");
    }
    return head->value;
  }
  bool isEmpty() const {
    return head == nullptr; // or length == 0
  }
};
