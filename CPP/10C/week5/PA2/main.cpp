#include "BSTree.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

void print(BSTree *BST) {
  cout << "Preorder = ";
  BST->preOrder();
  cout << endl;

  cout << "Inorder = ";
  BST->inOrder();
  cout << endl;

  cout << "Postorder = ";
  BST->inOrder();
  cout << endl;
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: " << endl;
  cout << "1. Insert" << endl
       << "2. Remove" << endl
       << "3. Print" << endl
       << "4. Search" << endl
       << "5. Smallest" << endl
       << "6. Largest" << endl
       << "7. Height" << endl
       << "8. Quit" << endl;
  cin >> choice;

  // Fix input + error checking
  if (cin.bad()) {
    throw runtime_error("Bad input");
  }
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  return choice;
}

int main() {
  BSTree BST;

  int choice = menu(); // Runs the menu and returns a value to choice

  string entry;
  // Any input after 7 is either invalid, or Quit
  while (choice < 8) {
    if (choice == 1) {
      cout << "Enter string to insert: ";
      getline(cin, entry);
      if (cin.bad()) {
        throw runtime_error("Bad input!");
      }
      cout << endl;

      BST.insert(entry);
    } else if (choice == 2) {
      cout << "Enter string to remove: ";
      getline(cin, entry);
      if (cin.bad()) {
        throw runtime_error("Bad input");
      }
      cout << endl;

      BST.remove(entry);
    } else if (choice == 3) {
      print(&BST);
    } else if (choice == 4) {
      cout << "Enter string to search for: ";
      getline(cin, entry);
      if (cin.bad()) {
        throw runtime_error("Bad input");
      }
      cout << endl;

      if (BST.search(entry)) {
        cout << "Found" << endl;
      } else {
        cout << "Not Found" << endl;
      }
    } else if (choice == 5) {
      cout << "Smallest: " << BST.smallest() << endl;
    } else if (choice == 6) {
      cout << "Largest: " << BST.largest() << endl;
    } else if (choice == 7) {
      cout << "Enter string: ";
      getline(cin, entry);
      if (cin.bad()) {
        throw runtime_error("Bad input!");
      }
      cout << endl;

      cout << "Height of subtree rooted at " << entry << ": "
           << BST.height(entry) << endl;
    }

    choice = menu(); // Keeps updating choice with menu function
  }

  return 0;
}
