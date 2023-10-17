#include "IntList.h"
#include <iostream>
#include <string>

using namespace std;

void menu(IntList *list) {
  cout << " IntList MENU" << endl;
  cout << "a - Add song(push_back)" << endl;       // done
  cout << "r - Add song(push_front)" << endl;      // done
  cout << "b - Remove song(pop_front)" << endl;    // done
  cout << "c - Remove song(pop_back)" << endl;     // done
  cout << "d - Output IntList in order" << endl;   // done
  cout << "e - Check is it empty" << endl;         // done
  cout << "o - Output IntList in reverse" << endl; // done
  cout << "q - Quit - Destructor" << endl;         // done
  cout << endl;
  cout << "Choose an option:";
  cout << endl;

  string choice;

  getline(cin, choice);

  if (choice == "q") {
    cout << "Calls destructor " << endl;
    delete list;
    return;
  } else if (choice == "o") {
    cout << "Printing list in reverse: ";
    list->printReverse();
    cout << endl;
    menu(list);
  } else if (choice == "a") {
    cout << "ADD IntNode push_back" << endl;
    int data;

    cout << "Enter node's data value:" << endl;
    cin >> data;
    cin.ignore();
    cout << endl;
    list->push_back(data);
    cout << "Normal: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl;

    menu(list);
  } else if (choice == "c") {
    cout << "Remove (pop_back)" << endl;
    list->pop_back();
    cout << "Normal: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl;

    menu(list);
  } else if (choice == "b") {
    cout << "Remove (pop_front)" << endl;
    list->pop_front();
    cout << "Normal: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl;
    menu(list);
  } else if (choice == "r") {
    cout << "ADD IntNode push_front " << endl;
    int data;

    cout << "Enter node's data value:" << endl;
    cin >> data;
    cin.ignore();
    cout << endl;
    list->push_front(data);
    cout << "Normal: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl;
    menu(list);
  } else if (choice == "e") {
    if (list->empty())
      cout << "list is empty" << endl;
    else
      cout << "list is not empty" << endl;
    menu(list);
  } else if (choice == "d") {
    cout << "Printing in order: " << *list << endl;
    cout << endl;
    menu(list);
  } else {
    menu(list);
  }
}
int main() {

  IntList *list = new IntList();
  menu(list);
  return -1;
}
