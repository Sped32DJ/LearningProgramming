void IntList::pop_front() {
  if (empty()) {
    throw runtime_error("List is empty");
  }
}

// Same goes with pop_back()
//
// Check PrintReverse()
// Check operator<<
// Check ~IntList()
// Make sure copy constructor exists
// Check all inputs
//
// DO PA2 for 10C and 61
// Finish zybooks
// update github
//
// Make sure to keep everything O(1)
// For queues, just a stack, easier to use than linked list
// You can use an array version... People hate it

// Stack, First in First Out
// FIFO
class ArrayQueue {
public:
  push(int value) { Array[(front + size) % capacity] = value; }
  // MODULE IS VERY IMPORTANT
  // This shit wraps around real nice
  pop() {
    ++front; // Where the array begins, no need to shift anything
             // Keeps the index
  }
  GetFront() {}
  resize() {
    // Front = 0, you unwrap it
    front = 0;
    size = size;
    capacity = capacity;
    for () {
    } // For loop to fill in the array, or just '=' operator
  }

private:
  // Always changing through pops and push
  int front;
  int size;

  int capacity; // max size, only changes when needs more RAM
}

// "deck"
// This is a doubly linked list (by the defs)
// There's a next and prev
// Keep track of both ends
class deque {
  push_front();
  push_back();
  pop_front();
  pop_back();
  is_empty();
}

// A stack is just a vector, push_back and pop_back
// LIFO
