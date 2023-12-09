#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

struct Vertex {
  list<pair<int, int>> neighbors;

  int a;
  int b;
  int distance;
  string decision;
  Vertex *prev;

  Vertex();
  ~Vertex();
  Vertex(int, int, int, string, Vertex *);
  Vertex(const Vertex &);
};

class Jug {
public:
  Jug(int, int, int, int, int, int, int, int, int);
  Jug(const Jug &);
  ~Jug();

  // solve is used to check input and find the solution if one exists
  // returns -1 if invalid inputs. solution set to empty string.
  // returns 0 if inputs are valid but a solution does not exist. solution set
  // to empty string. returns 1 if solution is found and stores solution steps
  // in solution string.
  int solve(string &);

private:
  void dijkstraMethod(vector<Vertex *> &, vector<Vertex *> &);
  string getPath(vector<Vertex *> &, int &);

  bool isPossible(vector<Vertex *> &) const;
  bool isInvalid(int, int, int, int, int, int, int, int, int) const;
  bool isDupe(Vertex *);

  void makeGraph(Vertex *vert);
  Vertex *generateNewState(Vertex *vert, size_t i, int &cost);
  Vertex *createPourVertex(Vertex *, const string &, int &, int);

  void addVerticies(Vertex *vert);
  void updateGraph(Vertex *, Vertex *, int);
  int updateCost(Vertex *, Vertex *);

  size_t findIndex(Vertex *);

  Vertex *findGoal(vector<Vertex *> &);

  vector<string> paths;       // THE path
  vector<Vertex *> verticies; // Holds the verticies

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
