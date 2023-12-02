#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

public:
  Node(const string &small)
      : small(small), large(""), countData(1), left(nullptr), right(nullptr),
        parent(nullptr) {}

private:
  string small;
  string large;
  int countData;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;
};

#endif
