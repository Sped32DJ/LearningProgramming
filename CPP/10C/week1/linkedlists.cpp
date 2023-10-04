#include <iostream>

using namespace std;

struct LinkList(int head) {
  int *head = head;
  head->next = nullptr;
  int *tail = head;
};

struct LinkList() {
  int *head = nullptr;
  head->next = nullptr;
  int *tail = nullptr;
};

struct LinkList(int head, int tail) {
  int *head = head;
  head->next = tail; // ->next not defined
  int *tail = tail;
};

int main() {
  LinkList p; // TODO  I know this is wrong
  return 0;
}
