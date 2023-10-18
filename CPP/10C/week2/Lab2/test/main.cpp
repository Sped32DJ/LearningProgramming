#include "IntList.h"
#include <iostream>
#include <string>
using namespace std;

void DisplayMenu(IntList *list);

int main() {
  IntList *list = new IntList();
  DisplayMenu(list);
  return 0;
}

// This menu loops recursively (recursion practice!)
void DisplayMenu(IntList *list) {
  cout << "Menu" << endl
       << "a - Add (push_back)" << endl
       << "s - Add (push_front)" << endl
       << "w - Remove (pop_front)" << endl
       << "e - Remove (pop_back)" << endl
       << "z - Output List in order" << endl
       << "x - Output list in reverse" << endl
       << "c - Check if empty" << endl;
  cout << endl;
  cout << "Choose an Option: ";
  cout << endl;

  char choice;
  cin >> choice;
  if (cin.fail()) {
    throw runtime_error("Bad input!");
  }
  choice.tolower();

  if (choice == 'q') {
    cout << "Call deconstructor" << endl;
    delete list;
    return;
  } else if (choice == 'a') {
    cout << "Pushing back node" << endl;
    int data;
    cin >> data;
    if (cin.fail()) {
      throw runtime_error("Bad data input");
    }
    list->push_back(data);

    // Recursion!
    DisplayMenu(list);
  } else if (choice == 'a') {
    cout << "IntNode push_back()" << endl;
    int data;

    cin >> data;
    if (cin.fail()) {
      throw runtime_error("Bad input");
    }
    list->push_back(data);

    DisplayMenu(list);
  } else if (choice == 's') {
    cout << "IntNode push_front()" << endl;
    int data;

    cin >> data;
    if (cin.fail()) {
      throw runtime_error("Bad input");
    }
    list->push_front(data);

    DisplayMenu(list);
  } else if (choice == 'w') {
    cout << "Remove (pop_front)" << endl;
    list->pop_front();

    DisplayMenu(list);
  } else if (choice == 'e') {
    cout << "Remove (pop_back)" << endl;
    list->pop_back();

    DisplayMenu(list);
  } else if (choice == 'z') {
    cout << "Output list in order" << endl;
    cout << *list << endl;

    DisplayMenu(list);
  } else if (choice == 'x') {
    cout << "Output list in reverse order" << endl;
    list->printReverse();

    DisplayMenu(list);
  } else if (choice == 'c') {
    cout << "Check if list if empty" << endl;
    list->empty();
  } else {
    // Will keep going until q, or runtime_error
    DisplayMenu(list);
  }
}
