#include <fstream>
#include <iostream>

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

arithmeticExpression::~arithmeticExpression() {}

// recursively deletes nodes
void arithmeticExpression::deleteTree(TreeNode *node) {
  if (node) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

void arithmeticExpression::buildTree() {
  string postfixExpr = infix_to_postfix();
  // Function to build a tree using postfix expression
  // root = buildTreeFromPostFix(postfix);
}

// Recursive expressions
void arithmeticExpression::infix() { infix(TreeNode * cpy); }
void arithmeticExpression::prefix() { prefix(TreeNode * cpy); }
void arithmeticExpression::postfix() { postfix(TreeNode * cpy); }
void visualizeTree(const string &data) {
  visualizeTree(ofstream & burner, TreeNode * cpy);
}
