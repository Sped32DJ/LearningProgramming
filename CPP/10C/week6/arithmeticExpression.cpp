#include "arithmeticExpression.h"
#include <fstream>
#include <iostream>
#include <sstream>
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
  ostringstream oss;
  char c;
  for (size_t i = 0; i < infixExpression.size(); ++i) {
    c = infixExpression.at(i);
    if (c == ' ') {
      continue;
    }

    if (isOperator(c)) { // c is an operator
      if (c == '(') {    // Pushes everything within parenthesis within a stack
        s.push(c);
      } else if (c == ')') {
        while (s.top() != '(') { // Loaded into buffer as it gets poped
          oss << s.top();
          s.pop();
        }
        s.pop();
      } else {
        while (!s.empty() && priority(c) <= priority(s.top())) { // If the
          //          priority of the operator is less than or equal to the
          //          priority of the
          //         operator on top of the stack
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
  while (!s.empty()) { // As long as the stack has
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
// Converts infix expression to postfix tree
void arithmeticExpression::buildTree() {
  // Convert infix to postfix
  string postfixExpr = infix_to_postfix();

  // Build tree from postfix
  root = buildTreeFromPostFix(postfixExpr);
}

TreeNode *
arithmeticExpression::buildTreeFromPostFix(const string &postfixExpr) {
  // A TreeNode stack
  stack<TreeNode *> nodeStack;
  int nodeKey = 0;

  for (size_t i = 0; i < postfixExpr.size(); ++i) {
    char ch = postfixExpr[i]; // Iterates through each char

    if (isOperand(ch)) { // gets pushed into stack if operand
      TreeNode *newNode = new TreeNode(ch, nodeKey);
      nodeStack.push(newNode);
      ++nodeKey;
    } else if (isOperator(ch)) { // If operator, stores operand and pops it
      TreeNode *operand2 = nodeStack.top();
      nodeStack.pop();
      TreeNode *operand1 = nodeStack.top();
      nodeStack.pop();

      TreeNode *newOperator = new TreeNode(ch, nodeKey);
      // Set expression's right and left to their node
      newOperator->left = operand1;
      newOperator->right = operand2;

      // Pushes new operator into stack
      nodeStack.push(newOperator);
      ++nodeKey;
    }
  }

  // Recursively loops top until it is empty
  if (!nodeStack.empty()) {
    return nodeStack.top();
  }

  return nullptr;
}

// NOTE  TO HERE, wtf

// Recursive expressions
// inorder, preorder, postorder logic
void arithmeticExpression::infix() {
  TreeNode *curr = root; // TODO  Should this be intialized to something?
  infix(curr);
}
void arithmeticExpression::prefix() {
  TreeNode *curr = root;
  prefix(curr);
}
void arithmeticExpression::postfix() {
  TreeNode *curr = root;
  postfix(curr);
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
    // infix is the only one that requires parenthesis
    if (curr->left) {
      cout << '(';
    }
    infix(curr->left);
    cout << curr->data;
    infix(curr->right);
    // Makes sure everything inside the expression
    // is closed in parenthesis
    if (curr->right) {
      cout << ')';
    }
  }
}

// Preorder logic
void arithmeticExpression::prefix(TreeNode *curr) {
  if (curr) {
    cout << curr->data;
    prefix(curr->left);
    prefix(curr->right);
  }
}

// postorder logic
void arithmeticExpression::postfix(TreeNode *curr) {
  if (curr) {
    postfix(curr->left);
    postfix(curr->right);
    cout << curr->data;
  }
}

// Helps clean up the code / increase readability
bool arithmeticExpression::isOperand(char ch) { return isalpha(ch); }
bool arithmeticExpression::isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || (ch == '(') ||
         (ch == ')');
}
