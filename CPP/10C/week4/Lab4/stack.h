#include <iostream>
#include <string>

using namespace std;

#ifndef __STACK_H__
#define __STACK_H__

// LIFO
template <class T> class stack {
private:
  static const int MAX_SIZE = 20;
  T *data;
  int size; // Represents accessible values
  int front;

public:
  // constructor
  // Make sure to get T template
  stack() : size(0), front(0) { data = new T[MAX_SIZE]; }

  // Parameterized constructor
  stack(T val) : size(0), front(0) { push(val); }

  // copy constructor
  stack(const stack &cpy) {
    size = cpy.size;
    front = cpy.front;
    std::copy(cpy.data, cpy.data + MAX_SIZE, data);
  }

  // Detructor
  ~stack() {
    delete[] data;
    size = 0;
  }

  void push(T val) {
    if (isFull()) {
      throw overflow_error("Called push on full stack.");
    }
    // Pushes to the front of the stack, then increments size
    data[(front + size) % MAX_SIZE] = val;
    ++size;
  }

  void pop() {
    if (empty()) {
      throw out_of_range("Called pop on empty stack.");
    }
    if (isFull()) {
      throw out_of_range("Reached max size");
    }
    top();
    --size; // Value is still in memory, but is now trash
            // Cheaper to "deallocate" then to overwrite
  }

  void pop_two() {
    // Checks range before it executes
    if (size < 2) {
      throw out_of_range("Called pop_two on a stack of size 1.");
    }
    size -= 2;
  }

  T top() {
    if (empty()) {
      throw underflow_error("Called top on empty stack.");
    }
    return data[(front + size - 1) % MAX_SIZE]; // TODO  Is this correct?
  }

  bool empty() const { return size == 0; }
  bool isFull() const { return size == MAX_SIZE; }
};

#endif
