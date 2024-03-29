#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "WordEntry.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

class HashTable {

private:
  list<WordEntry> *hashTable;
  int size;

public:
  HashTable(int);
  HashTable(const HashTable &);
  HashTable &operator=(const HashTable &);
  ~HashTable();

  void resize(int);
  bool contains(const string &);
  double getAverage(const string &);
  void put(const string &, int);

private:
  int computeHash(const string &);
};

#endif
