#include <stdio.h>
#include <stdlib.h>

// functions to implement
//
char *cptrCharToBinary(const unsigned char);
char cCharHexSelector(const unsigned char, const unsigned char);
char cIntHexSelector(const unsigned int, const unsigned char);

// create unsigned char and unsigned int variables here
int main(int argc, char *argv[]) {
  printf("1st Argument: argv[0]\n");

  printf("3rd Arugment: argv[2]\n");

  printf("argv[0] in binary: cptrCharToBinary(argv[0])\n");

  printf("lower 4 bits of argv[0]: cCharHexSelector(argv[0])\n");

  printf(
      "digit index argv[3] of argv[2] in hex is: cIntHexSelector(argv[3])\n");
  // write your code here
}

char *cptrCharToBinary(const unsigned char toBin) {
  int val = atoi(toBin);
  for (int i = 31; i >= 0; --i) {
  //  std::cout << ((n >> i) & 1); // Shift right and bitwise AND with 1 (C++)
  };
}

// implement your functions here
