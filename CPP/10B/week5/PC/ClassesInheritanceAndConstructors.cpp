#include <iostream>
using namespace std;

class B {
public:
  B() { cout << " B Cons"; }
  ~B() { cout << " B decon"; }
};
class D : public B {
public:
  D() { cout << " D cons"; }
  ~D() { cout << " D dcon"; }
};

int main() { D d; }
