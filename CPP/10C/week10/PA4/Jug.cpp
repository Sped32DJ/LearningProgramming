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

  // Takes care of all valid logic
  // Returns true if invalid
  if (isInvalid(Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA)) {
    throw runtime_error("Invalid, could not be constructed");
    return; // I think useless
  }

  paths.push_back("fill A");
  paths.push_back("fill B");
  paths.push_back("empty A");
  paths.push_back("empty B");
  paths.push_back("pour A B");
  paths.push_back("pour B A ");

  Vertex *origin = new Vertex();
  verticies.push_back(origin);
  makeGraph(origin);

  /* vector<int> unfinishedNs; // Holds the weights of the nodes
  findInGraph(0, 0, unfinishedNs);

  while (unfinishedNs.size() > 0) {

    // Get unfinished node
    int id = unfinishedNs.back();
    unfinishedNs.pop_back();

    // Get the node for jug A and B
    int A = graph[id].a;
    int B = graph[id].b;

    // State: filling A
    int fillA = findInGraph(Cb, B, unfinishedNs);

    // State: Filling B
    int fillB = findInGraph(A, Cb, unfinishedNs);

    // State: Empty A
    int emptyA = findInGraph(0, B, unfinishedNs);

    // State: Empty B
    int emptyB = findInGraph(A, 0, unfinishedNs);

    // Pour A to B
    // (s = volumetric Space (how much air jug holds))
    int sB = Cb - B;
    int pourSize = min(A, sB);
    int pourAtoB = findInGraph(A - pourSize, B + pourSize, unfinishedNs);

    // Pour B to A
    int sA = Ca - A;
    pourSize = min(B, sA);
    int pourBtoA = findInGraph(A + pourSize, B - pourSize, unfinishedNs);

    // Set six outedges for this vertex
    graph[id].newState[0] = fillA;
    graph[id].newState[1] = fillB;
    graph[id].newState[2] = emptyA;
    graph[id].newState[3] = emptyB;
    graph[id].newState[4] = pourAtoB;
    graph[id].newState[5] = pourBtoA;
  } */
}
void Jug::makeGraph(Vertex *vert) {
  FillAJug(vert);
  FillBJug(vert);
  EmptyAJug(vert);
  EmptyBJug(vert);
  pourAB(vert);
  pourBA(vert);

  for (auto neighbor : vert->neighbors) {
    makeGraph(verticies.at(neighbor.first));
  }
}

void Jug::FillAJug(Vertex *vert) {
  if (vert->a < Ca) {
    AddVertex(vert, Ca, vert->b, cfA);
  }
}

void Jug::FillBJug(Vertex *vert) {
  if (vert->b < Cb) {
    AddVertex(vert, vert->a, Cb, cfB);
  }
}

void Jug::EmptyAJug(Vertex *vert) {
  if (vert->a > 0) {
    AddVertex(vert, 0, vert->b, ceA);
  }
}

void Jug::EmptyBJug(Vertex *vert) {
  if (vert->b > 0) {
    AddVertex(vert, vert->a, 0, ceB);
  }
}

void Jug::pourAB(Vertex *vert) {
  if (vert->b < Cb && vert->a > 0) {
    Vertex *newVert = AddVertex(vert, vert->a, vert->b, 0);
    pourIntoJug(newVert, &Vertex::a, &Vertex::b, Cb, cpAB);
  }
}

void Jug::pourBA(Vertex *vert) {
  if (vert->a < Ca && vert->b > 0) {
    Vertex *newVert = AddVertex(vert, vert->a, vert->b, 0);
    pourIntoJug(newVert, &Vertex::b, &Vertex::a, Ca, cpBA);
  }
}

Vertex *Jug::AddVertex(Vertex *vert, int A, int B, int cost) {
  Vertex *newVert = new Vertex();
  newVert->a = A;
  newVert->b = B;
  newVert->decision = paths.at(i);
  addUniqueVertex(newVert);
  vert->neighbors.push_back(make_pair(verticies.size() - 1, cost));
  return newVert;
}

void Jug::pourIntoJug(Vertex *vert, int Vertex::*from, int Vertex::*to,
                      int toCapacity, int cost) {
  while ((vert->*to) < toCapacity && (vert->*from) > 0) {
    (vert->*to) += 1;
    (vert->*from) -= 1;
  }
}

void Jug::addUniqueVertex(Vertex *newVert) {
  bool duplicate = false;
  for (unsigned j = 0; j < verticies.size(); j++) {
    if (verticies.at(j)->a == newVert->a && verticies.at(j)->b == newVert->b) {
      duplicate = true;
    }
  }
  if (!duplicate) {
    verticies.push_back(newVert);
  } else {
    delete newVert;
  }
}

// Lecture code
/* int position = 0;
for (int i = 0; i <= Ca; ++i) {
  for (int j = 0; j <= Cb; ++j) {
    cout << "node " << position++ << ' ';
    cout << '(' << i << ',' << j << ')' << endl;
    // Empty A
    cout << "  " << '(' << 0 << ',' << j << ')' << " => " << pos(Cb, 0, j)
         << endl;
    // Empty B
    cout << "  " << '(' << i << ',' << 0 << ')' << " => " << pos(Cb, i, 0)
         << endl;
    // Fill A
    cout << "  " << '(' << Ca << ',' << j << ')' << " => " << pos(Cb, Ca, j)
         << endl;
    // Fill B
    cout << "  " << '(' << i << ',' << Cb << ')' << " => " << pos(Cb, i, Cb)
         << endl;
    // A to B
    int availableB = Cb - j;
    int movableToB = min(i, availableB);
    cout << "  " << '(' << i - movableToB << ',' << j + movableToB << ')'
         << " ==> " << pos(Cb, i - movableToB, j + movableToB) << endl;
    // B to A
    int availableA = Ca - i;
    int movableToA = min(j, availableA);
    cout << "  " << '(' << i + movableToA << ',' << j - movableToA << ')'
         << " ==> " << pos(Cb, i + movableToA, j - movableToA) << endl;
    //      G.emplace_ back(i, j, pos(Cb, 0, j),                  // Empty A
    //                     pos(Cb, i, 0),                         // Empty B
    //                      pos(Cb, Ca, 0),                       // Fill A
    //                     pos(Cb, i, Cb),                        // Fill B
    //                    pos(Cb, i - movableToB, j + movableToB),// A to B
    //                   pos(Cb, i + movableToA, j - movableToA)  // B to A
    //  )
  }
} // Everyting from here and up is lecture code */
/* int Jug::findInGraph(int A, int B, vector<int> &unfinishedV) {
  for (size_t i = 0; i < graph.size(); ++i) {
    if ((graph[i].a == A) && (graph[i].b == B)) {
      return i;
    }
  } */

// New combination
// Then add to the graph
/* int id = graph.size();
unfinishedV.push_back(id);
graph.push_back(Vertex(A, B, id));
return id;
} */

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

/* void Jug::printGraph() const {
  cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA\n";
  for (const auto &ver : graph) { // TODO  simplicity
    cout << ver.id << "\t(" << ver.a << ',' << ver.b << ')';
    for (int i = 0; i < 6; ++i) {
      printState(ver.newState[i]);
    }
    cout << endl;
  }
}

void Jug::printState(int i) const {
  cout << '\t' << i;
  if (i != -1) {
    cout << '(' << graph[i].a << ',' << graph[i].b << ')';
  }
} */

// solve is used to check input and find the solution if one exists
// returns -1 if invalid inputs. solution set to empty string.
// returns 0 if inputs are valid but a solution does not exist. solution set
// to empty string. returns 1 if solution is found and stores solution steps
// in solution string.
int Jug::solve(string &solution) {
  // invalid game
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

  solution = getPath(visited);

  return 1;
}

string Jug::getPath(vector<Vertex *> &visited) {
  Vertex *goal = 0;
  for (size_t i = 0; i < visited.size(); ++i) {
    if (visited.at(i)->a == 0 && visited.at(i)->b == N) {
      goal = visited.at(i);
    }
  }
  Vertex *curr = goal;
  Vertex *before = 0;
  stack<string> s;
  int cost;
  string path;

  while (curr) {
    string proposedSolution;
    before = curr->prev;
    if (before) {
      proposedSolution = curr->decision + '\n';
    }

    s.push(proposedSolution);

    if (before) {
      for (auto &neighbor : before->neighbors) {
        if (verticies.at(neighbor.first)->a == curr->a &&
            verticies.at(neighbor.first)->b == curr->b) {
          cost = cost + neighbor.second;
        }
      }
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
  bool isNegative = false;
  // Outputs true if a val is negative
  if (Ca < 0 || Cb < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 ||
      cpAB < 0 || cpBA < 0) {
    isNegative = true;
  }

  // Outputs true if invalid
  // Range check !valid && if a val is negative
  return !((0 < Ca && Ca <= Cb) && (N <= Cb && Cb <= 1000)) && isNegative;
}
