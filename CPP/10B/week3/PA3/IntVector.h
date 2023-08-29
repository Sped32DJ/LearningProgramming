#ifndef __INTVECTOR_H__
#define __INTVECTOR_H__

#include <iostream>
using namespace std;

class IntVector {
private:
  size_t _size;
  size_t _capacity;
  int *_data;
  void expand();
  void expand(size_t amount);

public:
  // NOTE For some reason, works better without capacity = 0
  IntVector(size_t capacity, int value = 0);
  /* IntVector(size_t capacity = 0); */
  IntVector();
  ~IntVector();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  int &at(size_t index); // NEW
  const int &at(size_t index) const;
  const int &front() const;
  const int &back() const;
  int &front();
  int &back();
  // Exclusive to PA vs Lab6
  void insert(size_t index, int value);
  void erase(size_t index);
  void assign(size_t n, int value);
  void push_back(int value);
  void pop_back();
  void clear();
  void resize(size_t n, int value = 0);
  void reserve(size_t n);
};

#endif
