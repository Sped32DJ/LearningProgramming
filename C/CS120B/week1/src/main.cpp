#include <stdio.h>
#include <stdlib.h>

// functions to implement
//
char *cptrCharToBinary(const unsigned char);
char cCharHexSelector(const unsigned char, const unsigned char);
char cIntHexSelector(const unsigned int, const unsigned char);

// create unsigned char and unsigned int variables here
int main(int argc, char *argv[]) {
  printf("1st argument: %s\n", argv[0]);

  printf("3rd arugment: %s\n", argv[2]);

  printf("%s in binary: %s\n", argv[0], cptrCharToBinary(argv[0]));
  // Not sure if %s will dereference cptrCharToBinary

  printf("lower 4 bits of %s: %s\n", argv[0], ccharhexselector(argv[0]));

  printf("digit index %s of %s in hex is: %s\n", argv[3], argv[2],
         cinthexselector(atoi(argv[3]), argv[2]));
  return 0;
};

char *cptrCharToBinary(const unsigned char val) {
  int n = atoi(val);
  char *bin; // Remember this is a pointer...

  // while n is not #0
  while (n != 0) {
    // Adding to right of string
    // Checking LMB
    // FIX: Not sure if it works for pointers
    if (n & 0x80) {
      bin += '1';
    } else {
      bin += '0';
    }
    // Popping off the top (LMB)
    n << 1;
  }

  bin += '\0';

  return bin;
};

char cCharHexSelector(const unsigned char nibble, const unsigned char bit) {
  // if bit == 0; lower nibble
  // if bit == 1; upper nibble
  // TODO: Return as hex instead int

  return (bit) ? atoi(nibble & 0x0F) : atoi(nibble >> 4);
};

char cIntHexSelector(const unsigned int val, const unsigned char index) {
  // TODO Convert the int
  // Make sure it outputs as a char
  return (val >> (index * 4));
};

// implement your functions here
