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

Vertex::Vertex() : a(0), b(0), distance(INT_MAX), decision(""), prev(nullptr) {}
Vertex::Vertex(const Vertex &cpy) {
  a = cpy.a;
  b = cpy.b;
  distance = cpy.distance;
  decision = cpy.decision;
  prev = cpy.prev;
}
Vertex::Vertex(int a, int b, int distance, string decision, Vertex *prev)
    : a(a), b(b), distance(distance), decision(decision), prev(prev) {}

Vertex::~Vertex() { neighbors.clear(); }

// Clears all the verticies
Jug::~Jug() {
  for (size_t i = 0; i < verticies.size(); i++) {
    delete verticies.at(i);
  }
  verticies.clear(); // clear vector
}

Jug::Jug(const Jug &cpy) {
  Ca = cpy.Ca;
  Cb = cpy.Cb;
  N = cpy.N;
  cfA = cpy.cfA;
  cfB = cpy.cfB;
  ceA = cpy.ceA;
  ceB = cpy.ceB;
  cpAB = cpy.cpAB;
  cpBA = cpy.cpBA;

  for (Vertex *v : cpy.verticies) {
    Vertex *newVertex = new Vertex(*v);
    verticies.push_back(newVertex);
  }
}

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
    int cost;
    Vertex *newVert = generateNewState(vert, i, cost);

    if (newVert != nullptr) {
      updateGraph(newVert, vert, cost);
    }
  }

  addVerticies(vert); // Adds verticies, starting at origin
}

// takes care of every case (state)
Vertex *Jug::generateNewState(Vertex *vert, size_t i, int &cost) {
  Vertex *newVert = nullptr;

  switch (i) {
  case 0: // Jug A fill possibility
    if (vert->a < Ca) {
      newVert = new Vertex(Ca, vert->b, paths.at(i), cost, cfA);
    }
    break;

  case 1: // Jug B fill possibility
    if (vert->b < Cb) {
      newVert = new Vertex(vert->a, Cb, paths.at(i), cost, cfB);
    }
    break;

  case 2: // Jug A empty possibility
    if (vert->a > 0) {
      newVert = new Vertex(0, vert->b, paths.at(i), cost, ceA);
    }
    break;

  case 3: // Jug B empty possibility
    if (vert->b > 0) {
      newVert = new Vertex(vert->a, 0, paths.at(i), cost, ceB);
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

// For pour vertex states
Vertex *Jug::createPourVertex(Vertex *vert, const string &decision, int &cost,
                              int costValue) {
  Vertex *newVert = new Vertex(*vert);
  newVert->decision = decision;
  cost = costValue;

  // Adjust values for pour
  while (newVert->b < Cb && newVert->a > 0) {
    newVert->b += 1;
    newVert->a -= 1;
  }

  return newVert;
}

void Jug::updateGraph(Vertex *newVert, Vertex *vert, int cost) {
  if (newVert != nullptr) {

    // If it isn't a dupe
    if (!isDupe(newVert)) {
      verticies.push_back(newVert);
      size_t index = findIndex(newVert); // returns index of vertex
      vert->neighbors.push_back(make_pair(index, cost));
    } else {
      // deletes dupes
      delete newVert;
      newVert = nullptr;
    }
  }
}

bool Jug::isDupe(Vertex *newVert) {
  for (size_t j = 0; j < verticies.size(); j++) {
    if (verticies.at(j)->a == newVert->a && verticies.at(j)->b == newVert->b) {
      return true;
    }
  }
  return false;
}

size_t Jug::findIndex(Vertex *newVert) {
  // searches to find vertex, returns index
  for (size_t j = 0; j < verticies.size(); j++) {
    if (verticies.at(j) == newVert) {
      return j;
    }
  }
  return 0;
}

// Ties verticies together
void Jug::addVerticies(Vertex *vert) {
  for (auto neighbor : vert->neighbors) {
    makeGraph(verticies.at(neighbor.first));
  }
}

void Jug::dijkstraMethod(vector<Vertex *> &graph, vector<Vertex *> &visited) {
  queue<Vertex *> unfinishedQ; // Q of vertex objects

  for (size_t i = 0; i < graph.size(); ++i) {
    graph.at(i)->distance = INT_MAX; // Set all distances to infinity
    graph.at(i)->prev = nullptr;     // previus node is null
  }

  graph.at(0)->distance = 0; // First node distance to it's self if 0!

  for (size_t i = 0; i < graph.size(); ++i) {
    unfinishedQ.push(graph.at(i));
  }

  while (!unfinishedQ.empty()) {
    // Keeps pushing back into the queue
    Vertex *curr = unfinishedQ.front();
    visited.push_back(curr); // adds to the back
    unfinishedQ.pop();       // pops from the front
    for (auto &neighbor : curr->neighbors) {
      // if (shortestPath), updates distanca
      if (graph.at(neighbor.first)->distance >
          curr->distance + neighbor.second) {
        graph.at(neighbor.first)->distance = curr->distance + neighbor.second;
        graph.at(neighbor.first)->prev = curr;
      }
    }
  }
}

// solve is used to check input and find the solution if one exists
// returns -1 if invalid inputs. solution set to empty string.
// returns 0 if inputs are valid but a solution does not exist. solution set
// to empty string. returns 1 if solution is found and stores solution steps
// in solution string.
int Jug::solve(string &solution) {

  // invalid game -> -1
  if (isInvalid(Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA)) {
    solution.clear();
    /* throw runtime_error("Graph is invalid"); */
    cerr << "Graph is invalid\n";
    return -1;
  }

  // Not possible -> 0
  if (!isPossible(verticies)) {
    /* throw runtime_error("unreachable from origin"); */
    cerr << "unreachable from origin\n";
    solution.clear();
    return 0;
  }

  vector<Vertex *> visited;           // will get modifed by dijkstraMethod
  dijkstraMethod(verticies, visited); // verticies now holds shortest paths
  int cost;
  solution = getPath(visited, cost); // solution now holds path

  return 1;
}

string Jug::getPath(vector<Vertex *> &visited, int &cost) {
  Vertex *goal = findGoal(visited);

  stack<string> s; // Needs a stack since we reach origin from end node
  string path;     // Will orgin -> end node path

  Vertex *curr = goal;
  Vertex *before = nullptr;
  int total = 0;

  while (curr) {
    string proposedSolution; // will hold unprocessed solution
    before = curr->prev;
    if (before) {
      proposedSolution = curr->decision + '\n';
    }

    // dijkstra Method gives us all paths
    // and in reverse, so push into stack
    // then order it!
    s.push(proposedSolution);

    if (before) {
      total += updateCost(before, curr); // Sum the cost as its being unwinded
    }
    // reset curr to prev, iterating backwards
    curr = before;
  }

  // Adding to path and popping from stack
  while (!s.empty()) {
    path += s.top(); // Paths adds from top of the stack
    s.pop();         // then pops to iterate until stack.empty()
  }
  return path + "success " + to_string(total);
}

// Returns the goal Vertex
Vertex *Jug::findGoal(vector<Vertex *> &visited) {
  for (size_t i = 0; i < visited.size(); ++i) {
    if (visited.at(i)->a == 0 && visited.at(i)->b == N) {
      return visited.at(i);
    }
  }
  return nullptr; // case where goal is unreachable
}

// returns true if goal can be reached
bool Jug::isPossible(vector<Vertex *> &verticies) const {
  for (size_t i = 0; i < verticies.size(); ++i) {
    if (verticies.at(i)->a == 0 && verticies.at(i)->b == N) {
      return true;
    }
  }
  return false; // Deemed not possible!
}

// returns the cost of the last vertex
int Jug::updateCost(Vertex *before, Vertex *curr) {
  int cost = 0;
  // Iterate over neighbors
  for (auto &neighbor : before->neighbors) {
    // if neighbors and curr share jug a & b vals
    if (verticies.at(neighbor.first)->a == curr->a &&
        verticies.at(neighbor.first)->b == curr->b) {
      cost += neighbor.second; // Add cost of neighbor
    }
  }
  return cost; // return sum
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
