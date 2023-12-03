#include "Jug.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB,
         int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB),
      cpBA(cpBA) {

  // Takes care of all valid logic
  // Returns true if invalid
  if (isInvalid(Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA)) {
    valid = false;
    return; // Can't return -1 because constructor
  }

  vector<int> unfinishedNs; // Holds the weights of the nodes
  findIngraph(0, 0, unfinishedNs);

  while (unfinishedNs.size() > 0) {

    // Get unfinished node
    int id = unfinishedNs.back();
    unfinishedNs.pop_back();

    // Get the node for jug A and B
    int A = graph[id].a;
    int B = graph[id].b;

    // State: filling A
    int fillA = findIngraph(Cb, B, unfinishedNs);

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
int Jug::findInGraph(int A, int B, vector<int> &unfinishedV) {
  for (size_t i = 0; i < graph.size(); ++i) {
    if ()
  }
  // FIX  Ended here
}

// Standardized code of the well known dijkstra's method
void Jug::dijkstraPath(Vertex &start) {

  queue<Vertex *> unfinishedQ; // Q of vertex objects

  for (size_t i = 0; i < graph.size(); ++i) {
    graph.at(i).distance = INT_MAX; // Set all distances to infinity
    graph.at(i).predV = nullptr;
  }

  start.distance = 0;
  unfinishedQ.push(&start); // The stack holds the path
  int otherPath;

  Vertex *otherVertices;
  Vertex *curr;

  int edgeWeight;
  int newState;

  while (!unfinishedQ.empty()) { // if empty start at curr and pop the queue
    curr = unfinishedQ.front();
    unfinishedQ.pop();

    for (size_t i = 0; i < curr->newState.size();
         ++i) { // Loops over all possibilities
      newState = curr->newState[i];
      if (newState != -1) { // edge weight
        otherPathVertices = &graph.at(newState);
        edgeWeight = getWeight(i);
        otherPath = curr->distance + edgeWeight;

        if (otherPath <
            otherVertices->distance) { // change verticies if shorter path
          otherVertices->distance = otherPath;
          otherVertices0->predV = curr;
          unfinishedQ.push(otherVertices);
        }
      }
    }
  }
}

Jug::~Jug() {}

// solve is used to check input and find the solution if one exists
// returns -1 if invalid inputs. solution set to empty string.
// returns 0 if inputs are valid but a solution does not exist. solution set
// to empty string. returns 1 if solution is found and stores solution steps
// in solution string.
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

int Jug::solve(string &solution) {
  if (solution == "")
    return -1;
  return 0;
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
