#include <iostream>
using namespace std;

class Point {
public:
  Point();
  void display(const Point &p);
  double getX() const;
  double getY() const;
  void move(double dx, double dy);
  Point add(const Point &) const;

private:
  double xCoord;
  double yCoord;
};

Point::Point() {
  xCoord = 0.0;
  yCoord = 0.0;
}
Point::Point(double x, double y) {
  xCoord = x;
  yCoord = y;
}

void Point::display(const Point &p) {
  // Implict parameter
  cout << '{' << this->xCoord << ',' << this->yCoord << '}';
}
// accessor, accesses private values
// mutator, modifies private values

double Point::getX() const { return xCoord; }
double Point::getY() const { return yCoord; }

void Point::move(double dx, double dy) {
  xCoord += dx;
  yCoord += dy;
}

// p3 = p1.add(p2);
Point Point::add(const Point &rhs) const {
  Point result;

  result.xCoord = this->xCoord + rhs.xCoord;
  result.yCoord = this->yCoord + rhs.yCoord;
  return result;
}

int main() {

  int n1;
  n1 = 10;
  cout << n1 << endl;

  Point p1;
  cout << "p1: ";
  p1.display(); // member function
  // display(p1); // global function
  cout << endl;

  /* Point p2 = Point(3.1, -1.35); */
  Point p2(3.1, -1.35);
  cout << "p2: ";
  p2.display();
  cout << endl;

  cout << p1.xCoord << endl;
  cout << p1.yCoord << endl;
}
