#include "Node.h"

Node::Node(string str) {
  data = str;
  left = nullptr;
  right = nullptr;
  count = 1;
}

// setters
void Node::setLeft(Node *newNode) { left = newNode; }

void Node::setRight(Node *newNode) { right = newNode; }

void Node::setData(string str) { data = str; }

void Node::setCount(int updatedCount) { count = updatedCount; }

// getters

int Node::getCount() const { return count; }

Node *Node::getLeft() const { return left; }

Node *Node::getRight() const { return right; }

string Node::getData() const { return data; }
