#include <iostream>

using namespace std;

void SayHi(string name, int age);

int main() {
  int num;
  num = 4;

  cout << "Tets" << endl;
  SayHi("Mike", 60);
  SayHi("Alan", 70);
  cout << "Top" << endl;

  return 0;
}

void SayHi(string name, int age) {
  cout << "Hello " << name << ","
       << " You are " << age << endl;
}
