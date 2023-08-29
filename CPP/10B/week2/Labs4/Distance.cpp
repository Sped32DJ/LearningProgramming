#include <iostream>
using namespace std;

#include "Distance.h"

Distance::Distance() {
  _feet = 0;
  _inches = 0.0;
  init();
}

Distance::Distance(unsigned ft, double in) {
  _feet = ft;
  _inches = in;
  init();
}

Distance::Distance(double in) {
  if (in < 0) {
    in *= -1;
  }
  _inches = in;
  _feet = static_cast<unsigned>(in / 12); // _feet is unsigned
  _inches -= _feet * 12;                  // take out the trash
  init();
}

unsigned Distance::getFeet() const { return _feet; }

double Distance::getInches() const { return _inches; }

double Distance::distanceInInches() const { return _feet * 12.0 + _inches; }

double Distance::distanceInFeet() const { return _feet + _inches / 12.0; }

double Distance::distanceInMeters() const { return distanceInFeet() * 0.3048; }

// operator time
Distance Distance::operator+(const Distance &rhs) const {
  Distance result;
  // convert everything to inches, then do math
  /* result._feet = _feet + rhs.getFeet(); */
  result._inches = distanceInInches() + rhs.distanceInInches();
  result.init();

  return result;
}

Distance Distance::operator-(const Distance &rhs) const {
  Distance result;

  /* result._feet = _feet - rhs.getFeet(); */
  result._inches = distanceInInches() - rhs.distanceInInches();

  result.init();

  return result;
}

ostream &operator<<(ostream &out, const Distance &rhs) {
  out << rhs.getFeet() << "' " << rhs.getInches() << '"';
  return out;
}

// Use this function to simply these numbers down
void Distance::init() {
  if (_inches < 0) {
    _inches *= -1;
  }

  while (_inches >= 12) {
    ++_feet;
    _inches -= 12;
  }
}
