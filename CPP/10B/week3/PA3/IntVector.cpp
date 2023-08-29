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

IntVector::~IntVector() {
  delete[] _data;
  _size = 0;
}

// NOTE  PASS
size_t IntVector::size() const { return _size; }

// NOTE  PASS
size_t IntVector::capacity() const { return _capacity; }

// NOTE  PASS
bool IntVector::empty() const { return _size == 0; }

// NOTE  PASS
// modifier
int &IntVector::at(size_t index) {
  if (index >= _size) {
    throw out_of_range("IntVector::at_range_check");
  }
  return _data[index];
}

// NOTE  PASS
// Accessor
const int &IntVector::at(size_t index) const {
  if (index >= _size) {
    throw out_of_range("IntVector::at_range_check");
  }
  /* return *(_data + index); // Pointer arithmatic */
  return _data[index]; // array notation
}

// NOTE  PASS
const int &IntVector::front() const {
  if (0 == _size) {
    throw out_of_range("IntVector::at_range_check");
  } else {
    return _data[0];
  }
}
// NOTE  PASS
int &IntVector::front() {
  if (0 == _size) {
    throw out_of_range("IntVector::at_range_check");
  } else {
    return _data[0];
  }
}

// NOTE  PASS
const int &IntVector::back() const {
  if (_size > 0) {
    return _data[_size - 1];
  } else {
    throw out_of_range("IntVector::at_range_check");
  }
}
// NOTE  PASS
int &IntVector::back() {
  if (_size > 0) {
    return _data[_size - 1];
  } else {
    throw out_of_range("IntVector::at_range_check");
  }
}

// NOTE  PASS
void IntVector::insert(size_t index, int value) {

  // range check
  if (index > _size) {
    throw out_of_range("IntVector::insert_range_check");
  }
  if (_size >= _capacity) {
    expand();
  }
  for (size_t i = _size; i > index; --i) {
    _data[i] = _data[i - 1]; // i+1 gives segfault
                             // Doesn't overwrite if reverse
  }
  _data[index] = value;

  ++_size;
}

// NOTE  PASS
void IntVector::erase(size_t index) {
  if (index >= _size) {
    throw out_of_range("IntVector::erase_range_check");
  }

  int *_temp = new int[_capacity];
  size_t j = 0;

  for (size_t i = 0; i < _size; ++i) {
    if (i == index) {
      // skips index
      continue;
    }
    _temp[j] = _data[i];
    ++j;
  }

  --_size;
  delete[] _data;
  _data = _temp;
}

// NOTE  PASS
void IntVector::assign(size_t n, int value) {
  if (n == _size) {
    return;
  }

  // NOTE  Supposed to use the largest _capacity possible
  // Prefer to double the capacity
  // Expensive

  if (n > _capacity) {
    if (n < _capacity * 2) {
      expand();
    } else {
      expand(n);
    }
  }

  for (size_t i = 0; i < n; ++i) {
    _data[i] = value;
  }

  _size = n;
}

// Push back into the array
// NOTE  PASS
void IntVector::push_back(int value) {
  if (_size >= _capacity) {
    expand();
  }
  _data[_size] = value;
  ++_size;
}

// NOTE  PASS
void IntVector::pop_back() {
  if (_size != 0) {
    --_size;
  }
  // NOTE  "It will never throw an exception"
}

// NOTE  Pass
void IntVector::clear() { _size = 0; }

// NOTE  PASS
void IntVector::resize(size_t n, int value) {

  // Only expands if required
  /* if (n > _capacity) {
    expand(n);
  } */
  if (n > _capacity) {
    if (n < _capacity * 2) {
      expand();
    } else {
      expand(n);
    }
  }

  for (size_t i = _size; i < n; ++i) {
    _data[i] = value;
  }
  _size = n;
}

// NOTE  PASS
void IntVector::reserve(size_t n) {
  int *_temp = nullptr; // remove out of scope error
  if (n > _size) {
    _temp = new int[n];
    for (size_t i = 0; i < _size; ++i) {
      _temp[i] = _data[i];
    }
  }
  delete[] _data;

  _data = _temp;
  // Reserving new space
  if (_capacity < n) {
    expand(n);
  }
}

// NOTE  Private Functions

// ++_size
// Realocate the memojry
void IntVector::expand() {
  if (_capacity == 0) {
    _capacity = 1;
  } else {
    _capacity *= 2;
  }

  int *_temp = new int[_capacity];
  for (size_t i = 0; i < _size; ++i) {
    _temp[i] = _data[i];
  }

  delete[] _data;
  _data = _temp;
}

void IntVector::expand(size_t amount) {
  int *_temp = new int[amount];
  for (size_t i = 0; i < _size; ++i) {
    _temp[i] = _data[i];
  }

  delete[] _data;
  _data = _temp;
  _capacity = amount;
}
