#include <iostream>
using namespace std;

class Book {
public:
  string title;
  string author;
  int pages;
  Book(string aTitle, string aAuthor, int aPages) {
    title = aTitle;
    author = aAuthor;
    pages = aPages;
  }
};

int main() {

  Book book1("Harry Potter", "JK Rowling", 500);
  /* book1.title = "Harry Potter";
  book1.author = "JK Rowling";
  book1.pages = 500; */

  Book book2("Lord of the Rings", "Tolkein", 700);
  /* book2.title = "Lord of the Rings";
  book2.author = "Tolkein";
  book2.pages = 700; */

  cout << book1.author << endl;
  cout << book2.author << endl;

  return 0;
}
