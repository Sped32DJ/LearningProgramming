#include <iostream>
using namespace std;

#include "Distance.h"

Distance Distance::Distance() {
  _feet = 0;
  _inches = 0.0;
}

Distance Distance::Distance(unsigned ft, double in) {
  _feet = ft + (in / 12);
  _inches = in % 12.0;
}

Distance Distance::Distance(double in) {
  _inches = in % 12.0;
  _feet = in / 12;
}

unsigned Distance::getFeet() const { return _feet; }

double Distance::getInches() const { return _inches; }

double Distance::distanceInInches() const { return _feet * 12.0 + _inches; }

double Distance::distanceInFeet() const { return _feet + _inches / 12.0; }

double Distance::distanceInMeters() const { return _feet + _inches / 12.0; }

// FIX  Both under may give over/underflow
Distance operator+(const Distance &rhs) const {
  Distance result;

  result._feet = _feet + rhs.getFeet;
  result._inches = _inches + rhs.getInches;

  return result;
}

Distance operator-(const Distance &rhs) const {
  Distance result;

  result._feet = _feet - rhs.getFeet;
  result._inches = _inches - rhs.getInches;

  return result;
}

ostream &operator<<(ostream &out, const Distance &rhs) {
  out << rhs.getFeet << "' " << rhs.getInches << '"' << endl;
}
