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

  printf("%s in binary: %s\n", argv[0], cptrchartobinary(argv[0]));

  printf("lower 4 bits of %s: %s\n", argv[0], ccharhexselector(argv[0]));

  printf("digit index %s of %s in hex is: %s\n", argv[3], argv[2],
         cinthexselector(atoi(argv[3]), argv[2]));
  return 0;
}

char *cptrCharToBinary(const unsigned char val) {
  int n = atoi(val);
  char *bin;
  for (int i = 31; i >= 0; --i) {
    printf("((n>>i)&1)\n"); // Shift right and btiwse AND with 1
  };
  return bin;
}

char cCharHexSelector(const unsigned char hex, const unsigned char) {}

// implement your functions here
