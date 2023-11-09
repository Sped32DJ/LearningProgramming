#include "Node.h"
#include <string>

using namespace std;

Node::Node() : data(""), left(nullptr), right(nullptr), count(0) {}
Node::Node(string data) : data(data), left(nullptr), right(nullptr), count(1) {}

// Modifiers
void Node::setData(string dataNew) { data = dataNew; }
void Node::setLeft(Node *nodeNew) { left = nodeNew; }
void Node::setRight(Node *nodeNew) { right = nodeNew; }
void Node::setCount(int updatedCount) { count = updatedCount; }

// Accessers
string Node::getData() const { return data; }
Node *Node::getLeft() const { return left; }
Node *Node::getRight() const { return right; }
int Node::getCount() const { return count; }
