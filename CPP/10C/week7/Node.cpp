#include "Node.h"
#include <string>

using namespace std;

Node::Node()
    : data(""), parent(nullptr), left(nullptr), right(nullptr), count(0) {}
Node::Node(const string &data)
    : data(data), parent(nullptr), left(nullptr), right(nullptr), count(1) {}

void Node::incrementCount() { ++count; }
void Node::decrementCount() { --count; }

bool Node::isLeaf() const { return !left && !right; }
bool Node::hasOneChild() const { return (!left && right) || (left && !right); }

bool Node::onlyLeft() const { return left && !right; }
bool Node::onlyRight() const { return !left && right; }
bool Node::isParent() const { return left && right; }
