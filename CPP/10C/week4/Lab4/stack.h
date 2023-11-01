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

public:
  // constructor
  stack() : size(0) { data = new T[MAX_SIZE]; }

  // Parameterized constructor
  stack(T val) : size(0) { push(val); }

  // copy constructor
  stack(const stack &cpy) {
    size = cpy.size;
    std::copy(cpy.data, cpy.data + MAX_SIZE, data);
  }

  // Detructor
  ~stack() {
    delete[] data;
    size = 0;
  }

  // Pushes to the top
  void push(T val) {
    if (isFull()) {
      throw overflow_error("Called push on full stack.");
    }
    data[size++] = val;
  }

  // Pops from the top
  T pop() {
    if (empty()) {
      throw out_of_range("Called pop on empty stack.");
    }
    return data[--size]; // decrements size then returns value
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
    return data[size - 1];
  }

  // two useful helper functions
  bool empty() const { return size == 0; }
  bool isFull() const { return size == MAX_SIZE; }
};

#endif
