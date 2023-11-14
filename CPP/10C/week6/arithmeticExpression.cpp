#include "arithmeticExpression.h"
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int arithmeticExpression::priority(char op) {
  int priority = 0;
  if (op == '(') {
    priority = 3;
  } else if (op == '*' || op == '/') {
    priority = 2;
  } else if (op == '+' || op == '-') {
    priority = 1;
  }
  return priority;
}

string arithmeticExpression::infix_to_postfix() {
  stack<char> s;
  // arithmeticExpression.cpp:23:17: error: aggregate ‘std::ostringstream oss’
  // has incomplete type and cannot be defined
  ostringstream oss;
  char c;
  for (unsigned i = 0; i < infixExpression.size(); ++i) {
    c = infixExpression.at(i);
    if (c == ' ') {
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' ||
        c == ')') { // c is an operator
      if (c == '(') {
        s.push(c);
      } else if (c == ')') {
        while (s.top() != '(') {
          oss << s.top();
          s.pop();
        }
        s.pop();
      } else {
        while (!s.empty() && priority(c) <= priority(s.top())) {
          if (s.top() == '(') {
            break;
          }
          oss << s.top();
          s.pop();
        }
        s.push(c);
      }
    } else { // c is an operand
      oss << c;
    }
  }
  while (!s.empty()) {
    oss << s.top();
    s.pop();
  }
  return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename) {
  ofstream outFS(outputFilename.c_str());
  if (!outFS.is_open()) {
    cout << "Error opening " << outputFilename << endl;
    return;
  }
  outFS << "digraph G {" << endl;
  visualizeTree(outFS, root);
  outFS << "}";
  outFS.close();
  string jpgFilename =
      outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}

// NOTE   ALL MY CODE BELOW HERE
arithmeticExpression::arithmeticExpression(const string &expr)
    : infixExpression(expr), root(nullptr) {}

// TODO
arithmeticExpression::~arithmeticExpression() { deleteTree(root); }

// recursively deletes nodes
void arithmeticExpression::deleteTree(TreeNode *node) {
  if (node) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

// NOTE HERE
void arithmeticExpression::buildTree() {
  string postfixExpr = infix_to_postfix();
  root = buildTreeFromPostFix(postfixExpr);
}

TreeNode *
arithmeticExpression::buildTreeFromPostFix(const string &postfixExpr) {
  stack<TreeNode *> nodeStack;
  int nodeKey = 0;

  for (char ch : postfixExpr) {
    if (isOperand(ch)) {
      TreeNode *newNode = new TreeNode('a' + nodeKey, ch);
      nodeStack.push(newNode);
      nodeKey++;
    } else if (isOperator(ch)) {
      TreeNode *operand2 = nodeStack.top();
      nodeStack.pop();
      TreeNode *operand1 = nodeStack.top();
      nodeStack.pop();

      TreeNode *newOperator = new TreeNode('a' + nodeKey, ch);
      newOperator->left = operand1;
      newOperator->right = operand2;

      nodeStack.push(newOperator);
      ++nodeKey;
    }
  }

  if (!nodeStack.empty()) {
    return nodeStack.top();
  }

  return nullptr;
}

bool arithmeticExpression::isOperand(char ch) { return isalpha(ch); }

bool arithmeticExpression::isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
// NOTE  TO HERE, wtf

// Recursive expressions
// inorder, preorder, postorder logic
void arithmeticExpression::infix() {
  TreeNode *curr = root; // TODO  Should this be intialized to something?
  infix(curr);
  cout << endl;
}
void arithmeticExpression::prefix() {
  TreeNode *curr = root;
  prefix(curr);
  cout << endl;
}
void arithmeticExpression::postfix() {
  TreeNode *curr = root;
  postfix(curr);
  cout << endl;
}

void arithmeticExpression::visualizeTree(ofstream &file, TreeNode *cpy) {
  if (!file.is_open()) {
    cerr << "Error: Unable to open file for visualization." << endl;
    return;
  }

  if (cpy != nullptr) {
    visualizeTree(file, cpy->left);
    file << "\"" << cpy->data << "\""
         << " [label=\"" << cpy->data << "\"]" << endl;

    if (cpy->left != nullptr)
      file << "\"" << cpy->data << "\""
           << " -> \"" << cpy->left->data << "\"" << endl;

    if (cpy->right != nullptr)
      file << "\"" << cpy->data << "\""
           << " -> \"" << cpy->right->data << "\"" << endl;

    visualizeTree(file, cpy->right);
  }
}

// Inorer, preorder, postorder logic
void arithmeticExpression::infix(TreeNode *curr) {
  if (curr) {
    infix(curr->left);
    cout << curr->data << " ";
    infix(curr->right);
  }
}

void arithmeticExpression::prefix(TreeNode *curr) {
  if (curr) {
    cout << curr->data << " ";
    prefix(curr->left);
    prefix(curr->right);
  }
}
void arithmeticExpression::postfix(TreeNode *curr) {
  if (curr) {
    postfix(curr->left);
    postfix(curr->right);
    cout << curr->data << " ";
  }
}
