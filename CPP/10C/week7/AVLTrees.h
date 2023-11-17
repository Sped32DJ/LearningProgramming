#include <iostream>

using namespace std;

class AVLTree {
public:
  void insert(const string &);
  int balanceFactor(Node *);
  void printBalanceFactors();
  void visualizeTree(const string &);

private:
  void findUnbalanceNode();
  void rotate();
  void rotateLeft();
  void printBalanceFactors(Node *);
  void visualizeTree(ofstream &, Node *);
};
