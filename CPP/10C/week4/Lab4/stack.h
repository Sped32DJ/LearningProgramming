#include <iostream>

using namespace std;

#ifndef __STACK_H__
#define __STACK_H__

// This template stack can hold string and ints
// LIFO
class stack {
public:
  // constructor
  // Make sure to get T template
  vector<T> stack() : size(0) {
    new stack = stack();
    tail = (front + size - 1) % MAX_SIZE;
  }
  // copy constructor

  // Detructor

  template <typename T> push(T val) {
    //(front + size - 1) % MAX_SIZE

    stack.at();
  }

  void pop() {
    // TODO  Obviously under is not valid
    if (empty()) {
      throw out_of_range("Can't pop empty stack");
    }
    if (size == max) {
      throw out_of_range("Reached max size");
    }
  }

  void pop_two() {
    pop();
    pop();
  }

  void top() {
    if (empty()) {
      throw underflow_error("Can't pop empty stack");
    }
    // Check if this works
    cout << "Top of stack is: " << stack[size - 1] << endl;
  }

  bool empty() {
    // MAX_SIZE only required for empty
    const int MAX_SIZE = 20;
    return size > MAX_SIZE;
  }

private:
  template <typename T> T data;
  int size;
  int start;
};

#endif
