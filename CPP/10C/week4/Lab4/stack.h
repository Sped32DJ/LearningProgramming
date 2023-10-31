#include <iostream>
#include <string>

using namespace std;

#ifndef __STACK_H__
#define __STACK_H__

// This template stack can hold string and ints
// LIFO
template <class T> class stack {
private:
  static const int MAX_SIZE = 20;
  T *data;
  int size;
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
    data[(front + size) % MAX_SIZE] = val; // or, (front+size-1) % MAX_SIZE
    ++size;
  }

  void pop() {
    if (empty()) {
      throw out_of_range("Called pop on empty stack.");
    }
    if (size == MAX_SIZE) {
      throw out_of_range("Reached max size");
    }
    top();
    --size;
    ++front;
  }

  void pop_two() {
    for (size_t i = 0; i < 2; ++i) {
      if (!empty()) {
        --size;
      }
      if (empty()) {
        /* throw out_of_range("Called pop_two on empty stack."); */
        throw out_of_range("Called pop_two on a stack of size 1.");
      }
      if (size == MAX_SIZE) {
        throw out_of_range("Called pop_two on a stack of size 1.");
      }
    }
  }

  T top() {
    if (empty()) {
      throw underflow_error("Called top on empty stack.");
    }
    return data[size - 1];
  }

  bool empty() { return size == 0; }
  // Better quality code to include this
  bool isFull() { return size == MAX_SIZE; }
};

#endif
