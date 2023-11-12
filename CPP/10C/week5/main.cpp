#include "Heap.h"
#include "PrintJob.h"
#include <iostream>

using namespace std;

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout << "1. Enqueue" << endl
       << "2. Print" << endl
       << "3. Dequeue" << endl
       << "4. Quit" << endl;
  cin >> choice;
  if (cin.bad() || cin.fail()) {
    throw runtime_error("Bad input");
  }

  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main() {
  Heap max_heap;

  int choice = menu();

  while (choice != 4) {

    if (choice == 1) {
      int priority, jobNumber, numPages;
      cout << "Enter print job to enqueue (priority, job Number, number of "
              "pages): ";
      cin >> priority >> jobNumber >> numPages;
      cout << endl;

      // Adds our new node to the heap
      max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));

    } else if (choice == 2) { // Prints the top of the stack(max)
      max_heap.print();
    } else if (choice == 3) { // pops from the top of the stack (removes max)
      max_heap.dequeue();
    }
    // fix buffer just in case non-numeric choice entered
    choice = menu();
  }
  return 0;
}
