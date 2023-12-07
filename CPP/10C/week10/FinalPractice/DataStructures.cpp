#include <iostream>
#include <stdexcept>
using namespace std;

template <template T> class queue {
private:
  struct Node {
    T data;
    Node *next;
    Node(const T &val) : data(val), next(nullptr) {}
  }

  public :

      queue()
      : front(nullptr), back(nullptr) {
  }

  ~queue() {
    while (!isEmpty()) {
      dequeue();
    }
  }
  void enqueue(const &T val) {
    Node *newNode = new Node(val);
    if (isEmpty()) {
      front = newNode;
      back = newNode;
    } else {
      back->next = newNode;
      back = newNode;
    }
  }

  // FIFO
  void dequeue() {
    if (isEmpty()) {
      throw runtime_error("queue is empty");
    }

    // hmmm
    Node *dummy = front;
    dummy = front->next;
    delete dummy;
    if (front == nullptr) {
      back == nullptr;
    }
  }
  T peek() const {
    if (isEmpty()) {
      throw runtime_error("queue is empty");
    }
    cout << front->data << endl;
  }
  bool isEmpty() const { return front == nullptr; }
};

// Array stack
template <template T> class stack {
private:
  static const int MAX_SIZE = 20;
  T *data;
  int size;

public:
  stack() : size(0) { data = new T[MAX_SIZE]; }
  stack(T val) : size(0) { push(val); }
  stack(const stack &cpy) {
    size = cpy.getSize();
    std::copy(cpy.data, cpy.data + MAX_SIZE, data);
  }
  ~stack() {
    delete[] data;
    size = 0;
  }
  // since push because name push_back redundant since LIFO
  void push(T val) {
    if (isFull()) {
      throw overflow_error("Can't push onto full stack");
    }
    data[size++] = data;
  }

  T pop() {
    if (empty()) {
      throw out_of_range("Can't pop empty stack")
    }
    return data[--size];
  }

  T pop_two() {
    if (size < 2) {
      throw out_of_range("Can't pop twice on stack size <2");
    }
    size -= 2;
  }
  T top() {
    if (empty()) {
      throw underflow_error("Can't top an empty stack");
    }
    return data[size - 1];
  }
};

// With dummies
template <template T> struct doublyLinkedList {
  struct Node {
    T data;
    Node *next;
    Node *prev;
    Node(const string &data) : data(data), next(nullptr), prev(nullptr) {}
  };
  Node dummy;

public:
};

struct array {};

// Maybe not this one too much
struct heap {};
