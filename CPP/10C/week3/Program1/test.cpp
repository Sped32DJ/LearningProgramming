#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  string payload;
  Node *next;
};

Node *newNode(string payload) {
  Node *newPerson = new Node;
  newPerson->payload = payload;
  newPerson->next = nullptr;
  return newPerson;
}

// Load/Print/Run are possibly problamatic
Node *loadGame(int n, vector<string> names) {
  if (n == 0 || names.empty()) { // check for empty list
    return nullptr;
  }

  Node *head = nullptr;
  Node *prev = nullptr;

  for (int i = 0; i < n; ++i) {
    string name = names.at(i);
    Node *newPerson = newNode(name);

    if (head == nullptr) {
      head = newPerson; // initialize head specially
    } else {
      prev->next = newPerson;
    }
    prev = newPerson;
  }

  if (prev != nullptr) {
    prev->next = head; // circular
  }

  return head;
}

void print(Node *start) { // prints list
  Node *curr = start;
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;

    if (curr == start) {
      break; // exit circular list
    }
  }
}

// FIXME  Bug somewhere here
Node *runGame(Node *start, int k) {
  Node *curr = start;
  Node *prev = nullptr;

  while (start->next != start) {
    for (int i = 0; i < k - 1; ++i) {
      prev = curr;
      curr = curr->next;
    }

    if (start == curr) {
      return start;
    }

    Node *tmp = curr;
    curr = curr->next;

    if (prev != nullptr) {
      prev->next = curr;
    } else {
      start = curr;
    }

    /* if (tmp == start) {
      start = curr;
    } */

    tmp->next = nullptr; // Break the link to prevent issues with delete
    delete tmp;
  }

  return start;
}

/* Driver program to test above functions */
int main() {
  int n = 1, k = 1, max; // n = num names; k = num skips (minus 1)
  string name;
  vector<string> names;

  // get inputs
  cin >> n >> k;
  if (cin.fail() || n <= 0 || k <= 0 || k > n) {
    throw runtime_error("Invalid input");
    return 1;
  }

  cout << "Gathering names" << endl;
  while (cin >> name && name != ".") {
    if (cin.fail()) {
      throw runtime_error("Invalid input");
      return 1;
    }
    names.push_back(name);
  } // EOF or . ends input

  cout << "initializing game" << endl;
  // initialize and run game
  Node *startPerson = loadGame(n, names);
  Node *lastPerson = runGame(startPerson, k);

  cout << "Looking for last person" << endl;
  if (lastPerson != nullptr) {
    cout << lastPerson->payload << " wins!" << endl;
  } else {
    cout << "error: null game" << endl;
  }

  cout << "Deleting people nodes" << endl;
  // Prevent memory leaks

  return 0;
}
