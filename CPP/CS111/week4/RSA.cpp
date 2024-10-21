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

unsigned int EulerTotient(unsigned int p, unsigned int q);

unsigned int modExp(unsigned int base, unsigned int exp, unsigned int mod);

// Uses Fermat's Little Theorem to check primality
bool isPrime(unsigned int p);

unsigned int modInverse(unsigned int a, unsigned int m);

// Fills our "hashmap"
void FillHash(vector<char> &map);

int main() {
  cout << "Solving the RSA" << endl;

  // Our dollar store hashmap
  vector<char> hmap;
  FillHash(hmap); // fill in the hashmap

  // The two prime numbers
  unsigned int p = 61;
  unsigned int q = 53;

  unsigned int n = p * q;

  // A chosen Encryption key
  unsigned int e = 17;

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
  // Check primality of p and q
  if (!isPrime(p) && !isPrime(q)) {
    cout << "both numbers must be prime" << endl;
    return 1;
  }

  // Check if p and q are the same
  if (p == q) {
    cout << "p and q cannot be the same" << endl;
    return 1;
  }

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

  // find decryption exponent
  int d = modInverse(e, EulerTotient(e, n));
  if (d < 0) {
    throw runtime_error(
        "Failed to find modular inverse for decryption exponent.");
  }

  string crackedMessage;

  for (int encryptedVal : message) {
    int decryptedVal = modExp(encryptedVal, d, n);

    // debug output
    if (decryptedVal >= 0 && decryptedVal < hmap.size()) {
      crackedMessage += hmap.at(decryptedVal);
    } else {
      crackedMessage += '?'; // placeholder
    }
  }

  return crackedMessage;
}

unsigned int EulerTotient(unsigned int p, unsigned int q) {
  return (p - 1) * (q - 1);
}

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

unsigned modInverse(unsigned int a, unsigned int p) {
  a = a % p;

  for (unsigned int x = 1; x < p; ++x) {
    if ((a * x) % p == 1) {
      return x;
    }
  }
  return 1;
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
