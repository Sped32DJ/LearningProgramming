#ifndef __INTVECTOR_H__
#define __INTVECTOR_H__

#include <iostream>
using namespace std;

class IntVector {
private:
  size_t _size;
  size_t _capacity;
  int *_data;

public:
  IntVector(size_t capacity, int value = 0);
  /* IntVector(size_t capacity = 0); */
  IntVector();
  ~IntVector();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  const int &at(size_t index) const;
  const int &front() const;
  const int &back() const;
};

#endif
