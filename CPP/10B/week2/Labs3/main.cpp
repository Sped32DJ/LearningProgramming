#include <cmath>
#include <iostream>

using namespace std;

// Rational Class declaration
class Rational {
private:
  int numerator;
  int denominator;

public:
  Rational();
  explicit Rational(int);
  Rational(int, int);
  Rational add(const Rational &rhs) const;
  Rational subtract(const Rational &rhs) const;
  Rational multiply(const Rational &rhs) const;
  Rational divide(const Rational &rhs) const;
  void simplify();
  void display() const;

private:
  int gcd(int num1, int num2) const;
  /* Rational simplify(Rational &rhs); */
};

// Constructors
Rational::Rational(int numerator, int denominator) {
  this->numerator = numerator;
  this->denominator = denominator;
}
Rational::Rational(int numerator) {
  this->numerator = numerator;
  denominator = 1;
}
Rational::Rational() {
  numerator = 0;
  denominator = 1;
}

// Implement Rational class member functions here
Rational Rational::add(const Rational &rhs) const {
  Rational result;

  // Messy, but does the job
  result.numerator =
      (numerator * rhs.denominator) + (rhs.numerator * denominator);
  result.denominator = denominator * rhs.denominator;

  // Simplifying, make it human readable
  result.simplify();

  return result;
}

Rational Rational::subtract(const Rational &rhs) const {
  Rational result;

  result.numerator =
      (numerator * rhs.denominator) - (rhs.numerator * denominator);
  result.denominator = (denominator * rhs.denominator);

  // Simplifying or else values too large
  result.simplify();

  return result;
}

Rational Rational::multiply(const Rational &rhs) const {
  Rational result;

  result.numerator = numerator * rhs.numerator;
  result.denominator = denominator * rhs.denominator;

  result.simplify();

  return result;
}

Rational Rational::divide(const Rational &rhs) const {
  Rational result;

  // Cross multiply
  result.numerator = numerator * rhs.denominator;
  result.denominator = denominator * rhs.numerator;

  result.simplify();

  return result;
}

// Useful for choosing GCD calculation
// Ex: 2 / 4, returns 1 / 2
// Thank you Wikipedia
int Rational::gcd(int num1, int num2) const {
  while (num2 != 0) {
    int temp = num2;
    num2 = num1 % num2;
    num1 = temp;
  }
  return num1;
}

void Rational::display() const { cout << numerator << " / " << denominator; }

// Just divides by gcd
void Rational::simplify() {
  int CommDenom = gcd(numerator, denominator);
  numerator /= CommDenom;
  denominator /= CommDenom;
}

// ===============================================
// Do not change any of the code below this line!!
// ===============================================

Rational getRational();
void displayResult(const string &op, const Rational &lhs, const Rational &rhs,
                   const Rational &result);

int main() {
  Rational A, B, result;
  char choice;

  cout << "Enter Rational A:" << endl;
  A = getRational();
  cout << endl;

  cout << "Enter Rational B:" << endl;
  B = getRational();
  cout << endl;

  cout << "Enter Operation:" << endl
       << "a - Addition (A + B)" << endl
       << "s - Subtraction (A - B)" << endl
       << "m - Multiplication (A * B)" << endl
       << "d - Division (A / B)" << endl
       << "y - Simplify A" << endl;
  cin >> choice;
  cout << endl;

  if (choice == 'a') {
    result = A.add(B);
    displayResult("+", A, B, result);
  } else if (choice == 's') {
    result = A.subtract(B);
    displayResult("-", A, B, result);
  } else if (choice == 'm') {
    result = A.multiply(B);
    displayResult("*", A, B, result);
  } else if (choice == 'd') {
    result = A.divide(B);
    displayResult("/", A, B, result);
  } else if (choice == 'y') {
    A.simplify();
    A.display();
  } else {
    cout << "Unknown Operation";
  }
  cout << endl;

  return 0;
}

Rational getRational() {
  int choice;
  int numer, denom;

  cout << "Which Rational constructor? (Enter 2, 1, or 0)" << endl
       << "2 - 2 parameters (numerator & denominator)" << endl
       << "1 - 1 parameter (numerator)" << endl
       << "0 - 0 parameters (default)" << endl;
  cin >> choice;
  cout << endl;

  if (choice == 2) {
    cout << "numerator? ";
    cin >> numer;
    cout << endl;
    cout << "denominator? ";
    cin >> denom;
    cout << endl;
    return Rational(numer, denom);
  } else if (choice == 1) {
    cout << "numerator? ";
    cin >> numer;
    cout << endl;
    return Rational(numer);
  } else {
    return Rational();
  }
}

void displayResult(const string &op, const Rational &lhs, const Rational &rhs,
                   const Rational &result) {
  cout << "(";
  lhs.display();
  cout << ") " << op << " (";
  rhs.display();
  cout << ") = (";
  result.display();
  cout << ")";
}
