#include <iostream>

template <typename T> class DoublyLinkedList {
private:
  struct Node {
    T data;
    Node *prev;
    Node *next;
    Node(const T &val) : data(val), prev(nullptr), next(nullptr) {}
  };

  Node *dummyHead;
  Node *dummyTail;

public:
  DoublyLinkedList() {
    dummyHead = new Node(T());
    dummyTail = new Node(T());
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
  }

  ~DoublyLinkedList() {
    while (!isEmpty()) {
      removeFront();
    }
    delete dummyHead;
    delete dummyTail;
  }

  void insertFront(const T &val) {
    Node *newNode = new Node(val);
    newNode->next = dummyHead->next;
    newNode->prev = dummyHead;
    dummyHead->next->prev = newNode;
    dummyHead->next = newNode;
  }

  void insertBack(const T &val) {
    Node *newNode = new Node(val);
    newNode->next = dummyTail;
    newNode->prev = dummyTail->prev;
    dummyTail->prev->next = newNode;
    dummyTail->prev = newNode;
  }

  void removeFront() {
    if (isEmpty()) {
      std::cerr << "List is empty. Cannot remove from the front.\n";
      return;
    }

    Node *temp = dummyHead->next;
    dummyHead->next = temp->next;
    temp->next->prev = dummyHead;
    delete temp;
  }

  void removeBack() {
    if (isEmpty()) {
      std::cerr << "List is empty. Cannot remove from the back.\n";
      return;
    }

    Node *temp = dummyTail->prev;
    dummyTail->prev = temp->prev;
    temp->prev->next = dummyTail;
    delete temp;
  }

  void display() const {
    Node *current = dummyHead->next;
    while (current != dummyTail) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

  bool isEmpty() const { return dummyHead->next == dummyTail; }
};

int main() {
  DoublyLinkedList<int> myList;

  myList.insertFront(10);
  myList.insertFront(5);
  myList.insertBack(20);
  myList.display(); // Output: 5 10 20

  myList.removeFront();
  myList.removeBack();
  myList.display(); // Output: 10

  return 0;
}
