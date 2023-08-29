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
  _inches = in;
  _feet = static_cast<unsigned>(in / 12); // _feet is unsigned
  _inches -= _feet * 12;                  // take out the trash
  init();
}

unsigned Distance::getfeet() const { return _feet; }

double distance::getinches() const { return _inches; }

double distance::distanceininches() const { return _feet * 12.0 + _inches; }

double distance::distanceinfeet() const { return _feet + _inches / 12.0; }

double distance::distanceinmeters() const { return distanceinfeet() * 0.3048; }

// operator time
distance distance::operator+(const distance &rhs) const {
  distance result;
  // convert everything to inches, then do math
  /* result._feet = _feet + rhs.getfeet(); */
  result._inches = distanceininches() + rhs.distanceininches();
  result.init();

  return result;
}

distance distance::operator-(const distance &rhs) const {
  distance result;

  /* double totalinches = distanceininches() - rhs.distanceininches();
  if (totalinches >= 0) {
    result._feet = static_cast<unsigned>(totalinches / 12);
    result._inches = totalinches - (result._feet * 12);
  } else {
    result._feet = static_cast<unsigned>(-((-totalinches) / 12));
    result._inches = 12 - (-totalinches - (result._feet * 12));
  } */
  double totalinches = distanceininches() - rhs.distanceininches();

  if (totalinches >= 0) {
    result._feet = static_cast<unsigned>(totalinches / 12);
    result._inches = totalinches - (result._feet * 12);
  } else {
    result._feet = static_cast<unsigned>(-((-totalinches) / 12));
    result._inches = -((-totalinches) - (result._feet * 12));
  }
  return result;
}

ostream &operator<<(ostream &out, const distance &rhs) {
  out << rhs.getfeet() << "' " << rhs.getinches() << '"';
  return out;
}

// use this function to simply these numebers down
void distance::init() {
  if (_inches >= 0.0) {
    while (_inches >= 12.0) {
      _inches -= 12.0;
      _feet += 1;
    }
  } else {
    while (_inches < 0.0) {
      _inches += 12.0;
      _feet -= 1;
    }
  }
}
