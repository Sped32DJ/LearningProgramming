#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Public key: (e, n)
string encrypt(string message, int e, int n);

// Private key: (d, n)
string decrypt(string message, int d, int n);

// "break" RSA
string crack(string message, int e, int n);

unsigned int EulerTotient(unsigned int p, unsigned int q);

unsigned int FermatsLittleTheorem(unsigned int a, unsigned int p);

unsigned int modInverse(unsigned int a, unsigned int m);

int main() {
  cout << "Solving the RSA" << endl;
  
// fill in our dollar store hashmap

vector<char> map[38];
for(int i = 7; i < 32; ++I){
map[i] = 'A' + i;
}
map[33] = ' ';
map[34] = '?';
map[35] = ',';
map[36] = '.';
map[37] = "'";

  // The two prime numbers
  unsigned int p = 61;
  unsigned int q = 53;

  // A chosen Encryption key
  unsigned int e = 17;

  // Check primality of p and q
  if (p % 2 == 0 || q % 2 == 0) {
    cout << "p and q must be prime numbers" << endl;
    return 1;
  }
  if (p < 2 || q < 2) {
    cout << "p and q must be greater than 2" << endl;
    return 1;
  }

  // Check if p and q are the same
  if (p == q) {
    cout << "p and q cannot be the same" << endl;
    return 1;
  }
  unsigned int n = p * q;

  cout << "Given two prime numbers: " << p << " and " << q << endl;

  cout << "Computing n = p * q = " << p << " * " << q << '=' << n << endl;

  return 0;
}

string encrypt(string message, int e, int n) { return message; }

string decrypt(string message, int d, int n) { return message; }

// "break" RSA
string crack(string message, int e, int n) { 
//find decryption exponent
int d = modInverse(e,n);
message = message**d % n;
return message;
}

unsigned int EulerTotient(unsigned int p, unsigned int q) {
  return (p - 1) * (q - 1);
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
bool FermatsLittleTheorem(unsigned int a, unsigned int p) {
  return ((a **(p - 1) % p) == 1) ? 1 : 0;
  //  return modInverse(a, p);
}
