#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Vertex {
  int a;
  int b;
  int id;
  int distance;
  Vertex *predV;
  vector<int> newState; // holds adjacent nodes

  Vertex(int a, int b, int id) : a(a), b(b), id(id), newState(6, -1) {}
};

class Jug {
public:
  Jug(int, int, int, int, int, int, int, int, int);
  ~Jug();

  // solve is used to check input and find the solution if one exists
  // returns -1 if invalid inputs. solution set to empty string.
  // returns 0 if inputs are valid but a solution does not exist. solution set
  // to empty string. returns 1 if solution is found and stores solution steps
  // in solution string.
  int solve(string &solution);
  void dijkstraMethod(Vectex &);
  int getWeight(int) const;

private:
  int findInGraph(int, int, vector<int> &);
  void showState(int) const;
  void printGraph() const;
  bool isInvalid(int, int, int, int, int, int, int, int, int) const;

  string solution;
  bool valid = true;
  vector<Vectex> graph;

  int Ca;   // capacity of jug a
  int Cb;   // capacity of jug b
  int N;    // goal capacity
  int cfA;  // cost fill a
  int cfB;  // cost fill b
  int ceA;  // cost empty a
  int ceB;  // cost empty b
  int cpAB; // cost pour A to B
  int cpBA; // cost pour B to A
};
