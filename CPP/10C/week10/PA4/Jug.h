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
  int solve(string &);

private:
  void dijkstraMethod(vector<Vertex *> &, vector<Vertex *> &);
  int getWeight(int) const;
  string getPath(vector<Vertex *> &, int &);

  void showState(int) const;

  bool isPossible(vector<Vertex *> &) const;
  bool isInvalid(int, int, int, int, int, int, int, int, int) const;

  // All used to make a graph
  /* void makeGraph(Vertex *vert);
  void FillAJug(Vertex *vert);
  void FillBJug(Vertex *vert);
  void EmptyAJug(Vertex *vert);
  void EmptyBJug(Vertex *vert);
  void pourAB(Vertex *vert);
  void pourBA(Vertex *vert);
  Vertex *AddVertex(Vertex *vert, int A, int B, int cost);
  void addUniqueVertex(Vertex *newVert);
  void pourIntoJug(Vertex *, int Vertex::*, int Vertex::*, int, int); */
  void makeGraph(Vertex *vert);
  Vertex *createNewVertex(Vertex *vert, size_t i, int &cost);
  Vertex *createVertexWithCapacity(Vertex *a, int, int, const string &, int &,
                                   int);
  Vertex *createPourVertex(Vertex *, const string &, int &, int);
  void updateGraph(Vertex *, Vertex *, int);
  int updateCost(Vertex *, Vertex *);
  bool isDupe(Vertex *);
  size_t findIndex(Vertex *);
  void addVerticies(Vertex *vert);

  Vertex *findGoal(vector<Vertex *> &);

  vector<string> paths;       // THE path
  vector<Vertex *> verticies; // The possibilities

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
