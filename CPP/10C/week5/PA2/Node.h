#ifndef __NODE_H__
#define __NODE_H__

#include "Node.h"
#include <string>

using namespace std;

class Node {
private:
  string data;
  Node *left;
  Node *right;
  int count;

public:
  Node();
  Node(string data);

  // Modifiers
  void setData(string);
  void setLeft(Node *);
  void setRight(Node *);
  void setCount(int);

  // Accessers
  string getData() const;
  Node *getLeft() const;
  Node *getRight() const;
  int getCount() const;
};

#endif
