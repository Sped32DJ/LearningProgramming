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
  newPerson->next = nullptr;
  newPerson->payload = payload;
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
  if (start == nullptr) {
    cout << "Empty List!" << endl;
    return;
  }

  Node *curr = start;
  while (curr != start || curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break;
    }
  }
  /* while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;

    if (curr == start) {
      break; // exit circular list
    }
  } */
}

// FIXME  Bug somewhere here
Node *runGame(Node *start, int k) { // josephus w circular list, k = num skips
  Node *curr = start;
  Node *prev = curr; // = curr; get inf loop

  while (curr->next != curr) {    // exit condition, last person standing
    for (int i = 0; i < k; ++i) { // find kth node
      prev = curr;
      curr = curr->next;

      /* cout << "Iteration: " << curr->payload; */
    }

    /* cout << "                        End of Round" << endl; */

    /* prev = prev->next->next; */
    prev->next = curr->next;
    delete curr;
    curr = prev->next;

    /* cout << "Test2.5" << endl; */
    cout << curr->payload << endl;
    /* cout << "Test2.8" << endl; */
  }
  /* cout << "Test3" << endl; */

  return curr; // last person standing (list links to it's self)
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

  while (cin >> name && name != ".") {
    if (cin.fail()) {
      throw runtime_error("Invalid input");
      return 1;
    }
    names.push_back(name);
  } // EOF or . ends input

  // initialize and run game
  Node *startPerson = loadGame(n, names);
  Node *lastPerson = runGame(startPerson, k);

  if (lastPerson != nullptr) {
    cout << lastPerson->payload << " wins!" << endl;
  } else {
    cout << "error: null game" << endl;
  }

  // Funny code causes memory leaks
  /* delete lastPerson;
  delete startPerson; */

  return 0;
}
