#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Public key: (e, n)
string encrypt(string message, int e, int n);

// Private key: (d, n)
string decrypt(string message, int d, int n);

// "break" RSA
string crack(vector<int> &message, int e, int n, const vector<char> &hmap);

int EulerTotient(int p, int q);

unsigned int modExp(unsigned int base, unsigned int exp, unsigned int mod);

int modularExponentiation(int base, int exp, int mod) {
  int result = 1;
  base = base % mod; // Handle base larger than mod

  while (exp > 0) {
    // If exp is odd, multiply base with result
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    // exp must be even now
    exp = exp >> 1;             // Divide exp by 2
    base = (base * base) % mod; // Square the base
  }
  return result;
}

// Uses Fermat's Little Theorem to check primality
// Function was never used, but quite useful
bool isPrime(unsigned int p);

int modInverse(int a, int m);

// Fills our "hashmap"
void FillHash(vector<char> &map);

int main() {
  cout << "Solving the RSA" << endl;

  // Our dollar store hashmap
  vector<char> hmap;
  FillHash(hmap); // fill in the hashmap

  vector<int> encoded = {
      1400, 764,  2088, 843,  2962, 99,   2979, 1443, 2382, 99,   2088, 4191,
      84,   843,  99,   843,  3780, 2218, 3237, 2218, 2962, 4191, 871,  843,
      3015, 99,   4191, 3780, 3780, 99,   764,  2088, 2218, 447,  2088, 99,
      2218, 2269, 99,   2218, 3237, 1032, 1443, 2269, 2269, 2218, 4242, 3780,
      843,  1691, 99,   871,  2088, 843,  2962, 99,   764,  2088, 4191, 871,
      843,  84,   843,  1655, 99,   1655, 843,  3237, 4191, 2218, 2962, 2269,
      1691, 99,   2088, 1443, 764,  843,  84,   843,  1655, 99,   2218, 3237,
      1032, 1655, 1443, 4242, 4191, 4242, 3780, 843,  1691, 99,   3237, 2382,
      2269, 871,  99,   4242, 843,  99,   871,  2088, 843,  99,   871,  1655,
      2382, 871,  2088, 2916, 1400};

  // Encryption key (given by problem)
  unsigned int e = 7;

  // n, (given by problem)
  unsigned int n = 4453;

  cout << "test\n";

  // Actual cracking
  cout << "Cracking the RSA"
       << crack(encoded, static_cast<int>(e), static_cast<int>(n), hmap)
       << endl;
  return 0;
}

// string encrypt(string message, int e, int n) { return pow(message, e) % n; }

// string decrypt(string message, int d, int n) { return pow(message, d) % n; }

string encrypt(string message, int e, int n) {
  string encrypted;
  for (char c : message) {
    int m = static_cast<int>(c);
    int enc = modExp(m, e, n);
    encrypted += static_cast<char>(enc);
  }
  return encrypted;
}

string decrypt(string message, int d, int n) {
  string decrypted;
  for (char c : message) {
    int enc = static_cast<int>(c);
    int m = modExp(enc, d, n);
    decrypted += static_cast<char>(m);
  }
  return decrypted;
}

// "break" RSA
string crack(vector<int> &message, int e, int n, const vector<char> &hmap) {
  cout << "test2\n";

  // Find p and q
  // n = p * q
  int p, q;

  // i += 2 to skip even numbers
  for (int i = 3; i < sqrt(n); i += 2) {
    if (!(n % i)) {
      p = i; // p is the current val of i
      i = n; // stops further iterations
    }
  }
  q = n / p; // Find q from p
  int phi_n = EulerTotient(p, q);

  cout << "n = " << n << endl;
  cout << "phi(n) = " << phi_n << endl;
  cout << "e = " << e << endl;
  cout << "p = " << p << endl << "q = " << q << endl;
  // Find d
  // d = e^-1 (mod phi(n))
  int d = modInverse(e, phi_n);
  cout << "d = " << d << endl;
  cout << "n = " << n << endl;
  // FIX:
  if (d * e == (1 % phi_n)) {
    cout << "d is verified\n";
  } else {
    cout << "not verified\n";
  }

  string crackedMessage;

  for (double encryptedVal : message) {
    int decryptedVal = modularExponentiation(encryptedVal, d, n);
    // debug output
    if (decryptedVal >= 0 && decryptedVal < hmap.size()) {
      crackedMessage += hmap.at(decryptedVal);
    } else {
      crackedMessage += 'e'; // placeholder
    }
  }

  return crackedMessage;
}

int EulerTotient(int p, int q) { return (p - 1) * (q - 1); }

unsigned int modExp(unsigned int base, unsigned int exp, unsigned int mod) {
  unsigned int result = 1;
  base = base % mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    exp /= 2;
    base = (base * base) % mod;
  }
  return result;
}

int modInverse(int a, int p) {
  int m0 = p, y = 0, x = 1;

  if (p == 1)
    return 0; // No inverse

  while (a > 1) {
    // q is quotient
    int q = a / p;
    int t = p;

    // p is the remainder
    p = a % p;
    a = t;
    t = y;

    y = x - q * y;
    x = t;
  }

  // Makes x positive
  if (x < 0) {
    x += m0;
  }
  //  return (x + p) % p;
  return (x + m0) % m0;
}

// Proves primality of a non-carmichael numbers
// using Fermat's Little Theorem
bool isPrime(unsigned int p) {
  if (p <= 2) {
    return 0;
  }

  unsigned int a = 2;
  if (!(2 % p)) {
    return 0; // a is dibilible by p
  }

  unsigned int result = 1;
  a = a % p; // take modulo of prime

  unsigned int exp = p - 1; // exponent for Fermat's

  // My IDE said I can't use pow
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * a) % p;
    }
    exp /= 2;
    a = (a * a) % p;
  }
  return result == 1; // Check congruency
}

void FillHash(vector<char> &map) {
  if (map.size() != 38) {
    map.resize(38);
  }

  for (int i = 7; i < 33; ++i) {
    map.at(i) = 'A' + (i - 7);
  }
  map.at(33) = ' ';
  map.at(34) = '?';
  map.at(35) = ',';
  map.at(36) = '.';
  map.at(37) = '\'';
}
