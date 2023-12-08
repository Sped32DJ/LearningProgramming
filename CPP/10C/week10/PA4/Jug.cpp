#include "Jug.h"
#include <climits>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

Vertex::Vertex() : a(0), b(0), distance(INT_MAX), decision(""), prev(0) {}
Vertex::~Vertex() { neighbors.clear(); }

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB,
         int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB),
      cpBA(cpBA) {

  paths.push_back("fill A");
  paths.push_back("fill B");
  paths.push_back("empty A");
  paths.push_back("empty B");
  paths.push_back("pour A B");
  paths.push_back("pour B A ");

  Vertex *origin = new Vertex();
  verticies.push_back(origin);
  makeGraph(origin);
}

void Jug::makeGraph(Vertex *vert) {
  for (size_t i = 0; i < paths.size(); ++i) {
    int cost = 0;
    Vertex *newVert = createNewVertex(vert, i);

    if (newVert != nullptr) {
      updateGraph(newVert, vert, cost);
    }
  }

  addVerticies(vert);
}

Vertex *Jug::createNewVertex(Vertex *vert, size_t i) {
  Vertex *newVert = nullptr;
  int cost; // TESTING cost declared here

  switch (i) {
  case 0: // Jug A fill possibility
    if (vert->a < Ca) {
      newVert =
          createVertexWithCapacity(vert, Ca, vert->b, paths.at(i), cost, cfA);
    }
    break;

  case 1: // Jug B fill possibility
    if (vert->b < Cb) {
      newVert =
          createVertexWithCapacity(vert, vert->a, Cb, paths.at(i), cost, cfB);
    }
    break;

  case 2: // Jug A empty possibility
    if (vert->a > 0) {
      newVert =
          createVertexWithCapacity(vert, 0, vert->b, paths.at(i), cost, ceA);
    }
    break;

  case 3: // Jug B empty possibility
    if (vert->b > 0) {
      newVert =
          createVertexWithCapacity(vert, vert->a, 0, paths.at(i), cost, ceB);
    }
    break;

  case 4: // Pour A into B
    if (vert->b < Cb && vert->a > 0) {
      newVert = createPourVertex(vert, paths.at(i), cost, cpAB);
    }
    break;

  case 5: // Pour B into A
    if (vert->a < Ca && vert->b > 0) {
      newVert = createPourVertex(vert, paths.at(i), cost, cpBA);
    }
    break;

  default:
    break;
  }

  return newVert;
}

Vertex *Jug::createVertexWithCapacity(Vertex *vert, int a, int b,
                                      const string &decision, int &cost,
                                      int costValue) {
  Vertex *newVert = new Vertex();
  newVert->a = a;
  newVert->b = b;
  newVert->decision = decision;
  cost = costValue;
  return newVert;
}

Vertex *Jug::createPourVertex(Vertex *vert, const string &decision, int &cost,
                              int costValue) {
  Vertex *newVert = createVertexWithCapacity(vert, vert->a, vert->b, decision,
                                             cost, costValue);
  while (newVert->b < Cb && newVert->a > 0) {
    newVert->b += 1;
    newVert->a -= 1;
  }
  return newVert;
}

void Jug::updateGraph(Vertex *newVert, Vertex *vert, int cost) {
  if (newVert != nullptr) {
    bool duplicate = isDupe(newVert);

    if (!duplicate) {
      verticies.push_back(newVert);
      size_t index = findIndex(newVert);
      vert->neighbors.push_back(make_pair(index, cost)); // Doesn't have cost
    } else {
      delete newVert;
      newVert = nullptr;
    }
  }
}

bool Jug::isDupe(Vertex *newVert) {
  for (size_t j = 0; j < verticies.size(); j++) {
    if (verticies[j]->a == newVert->a && verticies[j]->b == newVert->b) {
      return true;
    }
  }
  return false;
}

size_t Jug::findIndex(Vertex *newVert) {
  size_t index = 0;
  for (size_t j = 0; j < verticies.size(); j++) {
    if (verticies[j] == newVert) {
      index = j;
      break;
    }
  }
  return index;
}

void Jug::addVerticies(Vertex *vert) {
  for (auto neighbor : vert->neighbors) {
    makeGraph(verticies.at(neighbor.first));
  }
}

// Standardized code of the well known dijkstra's method
void Jug::dijkstraMethod(vector<Vertex *> &graph, vector<Vertex *> &visited) {
  queue<Vertex *> unfinishedQ; // Q of vertex objects

  for (size_t i = 0; i < graph.size(); ++i) {
    graph.at(i)->distance = INT_MAX; // Set all distances to infinity
    graph.at(i)->prev = nullptr;
  }

  graph.at(0)->distance = 0;

  for (size_t i = 0; i < graph.size(); ++i) {
    unfinishedQ.push(graph.at(i));
  }

  while (!unfinishedQ.empty()) {
    Vertex *curr = unfinishedQ.front();
    visited.push_back(curr);
    unfinishedQ.pop();
    for (auto &neighbor : curr->neighbors) {
      if (graph.at(neighbor.first)->distance >
          curr->distance + neighbor.second) {
        graph.at(neighbor.first)->distance = curr->distance + neighbor.second;
        graph.at(neighbor.first)->prev = curr;
      }
    }
  }
}

// TODO
Jug::~Jug() {}

// solve is used to check input and find the solution if one exists
// returns -1 if invalid inputs. solution set to empty string.
// returns 0 if inputs are valid but a solution does not exist. solution set
// to empty string. returns 1 if solution is found and stores solution steps
// in solution string.
int Jug::solve(string &solution) {
  // invalid game
  //
  if (isInvalid(Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA)) {
    solution.clear();
    return -1;
  }

  if (!isPossible(verticies)) {
    solution.clear();
    return 0;
  }
  vector<Vertex *> visited;           // will get modifed by dijkstraMethod
  dijkstraMethod(verticies, visited); // verticies now holds shortest path
  int cost;                           // TESTING  cost declared
  solution = getPath(visited, cost);

  return 1;
}

string Jug::getPath(vector<Vertex *> &visited, int &cost) {
  Vertex *goal = findGoal(visited);

  stack<string> s;
  string path;

  Vertex *curr = goal;
  Vertex *before = nullptr;

  while (curr) {
    string proposedSolution;
    before = curr->prev;
    if (before) {
      proposedSolution = curr->decision + '\n';
    }

    s.push(proposedSolution);

    if (before) {
      cost = updateCost(before, curr);
    }
    // reset curr to prev
    curr = before;
  }

  while (!s.empty()) {
    path = path + s.top();
    s.pop();
  }
  return path + "success " + to_string(cost);
}

Vertex *Jug::findGoal(vector<Vertex *> &visited) {
  for (size_t i = 0; i < visited.size(); ++i) {
    if (visited.at(i)->a == 0 && visited.at(i)->b == N) {
      return visited.at(i);
    }
  }
  return nullptr;
}

int Jug::updateCost(Vertex *before, Vertex *curr) {
  int cost = 0;
  for (auto &neighbor : before->neighbors) {
    if (verticies.at(neighbor.first)->a == curr->a &&
        verticies.at(neighbor.first)->b == curr->b) {
      cost += neighbor.second;
    }
  }
  return cost;
}

bool Jug::isPossible(vector<Vertex *> &verticies) const {
  for (size_t i = 0; i < verticies.size(); ++i) {
    if (verticies.at(i)->a == 0 && verticies.at(i)->b == N) {
      return true;
    }
  }
  return false; // whole loop ran, deemed not possible!
}

int Jug::getWeight(int index) const {
  switch (index) {
  case 0:
    return cfA;
  case 1:
    return cfB;
  case 2:
    return ceA;
  case 3:
    return ceB;
  case 4:
    return cpAB;
  default:
    return cpBA;
  }
}

// outputs true if invalid
bool Jug::isInvalid(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB,
                    int cpAB, int cpBA) const {
  // You will want to verify the costs are positive and
  // 0 < Ca ≤ Cb and N ≤ Cb ≤ 1000. If the inputs are invalid solve
  // will return -1
  // Outputs true if a val is negative
  if (Ca < 0 || Cb < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 ||
      cpAB < 0 || cpBA < 0) {
    return true;
  }

  // Outputs true if invalid
  // Range check !valid && if a val is negative
  return !((0 < Ca && Ca <= Cb) && (N <= Cb && Cb <= 1000));
}
