#include <iostream>
using namespace std;

class DLL {
  struct Node {
    string val;
    Node *next;
    Node *prev;
    Node(const string &val) : val(val), next(nullptr), prev(nullptr) {}
  };

  Node dummy;

public:
  DLL() {
    dummy.next = nullptr;
    dummy.prev = nullptr;
  }
  ~DLL() {
    // gotta delete all the links in the list
  }
  DLL(const DLL &) = delete;
  DLL &operator=(DLL &) = delete;

  void insert(const string &name) {
    Node *newnode = new Node(name);

    // Forward pointers
    dummy.head = newnode;
    newnode->prev = dummy;

    newnode->next = dummy.next; // both pointing same direction
    if (dummy->next != nullptr) {
      dummy.next->prev = newnode;
    }

    dummy.next = newnode;

    // rearward pointers
    newnode->prev = &dummy;
  }
};

// Circular sort is a circular linked list
//
// Bucket sort
// Putting all the values into different buckets.
//      Like grouping things depending on their GCD
//      Or in buckets based off their 10s place
//      O(N), single sort
//      Burns a lot of memory
//      Takes a lot more space, is faster

int main() {
  // Data structures are complex
  // Some will have more edge cases then others
  // Every single for loop will look like this
  Node *curr = nullptr;
  Node *prev = nullptr;
  for (curr = head; curr != nullptr; curr = curr->next) {
    if (curr->val == = 'b')
      break;
    prev = curr;
  }

  // Using a dummy node, decrease complexity
  // This helps since previous is never pointing into null
  // Decreases the edge cases of doubly-linked lists
  //    Runs faster
  // This is set to null once, never changed
  Node *dummy = nullptr;

  return 0;
}
