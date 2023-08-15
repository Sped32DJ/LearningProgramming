int Rational::gcd(int num1, int num2) const {
  if (num2 == 0) { // if denominator = 0
    return num1;
  }
  return gcd(num2, num1 % num2);
}

