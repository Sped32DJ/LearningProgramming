#include <iostream>
#include <string>
using namespace std;

int main() {

  int age = 19;
  int *pAge = &age;
  double gpa = 2.7;
  double *pGpa = &gpa;
  string name = "Mike";
  string *pName = &name;

  cout << "Age: " << &age << endl;
  cout << "alt: " << pAge << endl;
  cout << "Gpa: " << &gpa << endl;
  cout << "Name: " << &name << endl;

  cout << "\n" << &*&gpa << endl;
  cout << "\n" << *&gpa << endl;

  return 0;
}
