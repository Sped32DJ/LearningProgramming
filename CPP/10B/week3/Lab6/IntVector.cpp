#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
#include "IntVector.h"

IntVector::IntVector(size_t capacity, int value)
    : _size(capacity), _capacity(capacity) {

  if (capacity == 0) {
    throw out_of_range("IntVector::at_range_check");
  } else {
    // declares array + fills
    _data = new int[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
      _data[i] = value;
    }
  }
}

IntVector::IntVector() : _size(0), _capacity(0), _data(nullptr) {}

/* IntVector::IntVector() {
  _capacity = 0;
  _size = 0;
  _data = nullptr;
} */

IntVector::~IntVector() {
  delete[] _data;
  _size = 0;
}

// NOTE  PASS
size_t IntVector::size() const { return _size; }

// TODO  Make this proper
size_t IntVector::capacity() const { return _capacity; }

// NOTE  PASS
bool IntVector::empty() const {
  // Despite the lesser than equal to statement,
  // _size should never be 0<
  // returns the argument
  return _size == 0;
}
const int &IntVector::at(size_t index) const {
  /* return *(_data + index); */
  if (index >= _size) {
    throw out_of_range("IntVector::at_range_check");
  }
  /* return *(_data + index); // Pointer arithmatic */
  return _data[index]; // array notation
}

const int &IntVector::front() const {
  if (0 == _size) {
    throw out_of_range("IntVector::at_range_check");
  } else {
    return _data[0];
  }
}

// TEST
const int &IntVector::back() const {
  if (_size > 0) {
    return _data[_size - 1];
  } else {
    throw out_of_range("IntVector::at_range_check");
  }
}
