#include <stdio.h>
#include <stdlib.h>

// functions to implement
//
char *cptrCharToBinary(const unsigned char);
char cCharHexSelector(const unsigned char, const unsigned char);
char cIntHexSelector(const unsigned int, const unsigned char);

// create unsigned char and unsigned int variables here
int main(int argc, char *argv[]) {
  // NOTE: Do I need to free any memory?
  // argv[0] = .pio/build/stable/program
  // argv[1] = (actual input)
  printf("1st argument: %s\n", argv[1]);

  printf("3rd arugment: %s\n", argv[3]);

  char *binary = cptrCharToBinary(*argv[1]);
  printf("%s in binary: %s\n", argv[1], binary);
  free(binary);

  printf("lower 4 bits of %s: %c\n", argv[1],
         cCharHexSelector(atoi(argv[1]), *argv[3]));
  // NOTE: Why pass atoi?
  // %c passes a char string

  printf("digit index %s of %s in hex is: %c\n", argv[4], argv[3],
         cIntHexSelector(atoi(argv[4]), strtoul(argv[3], NULL, 10)));
  // NOTE: What does strtoul do?

  return 0;
};

char *cptrCharToBinary(const unsigned char val) {
  /* int n = atoi(val); */
  char *bin = (char *)malloc(sizeof(char[9])); // Remember this is a pointer...

  /* // while n is not #0
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
  } */

  // Start from the beginning
  for (int i = 7; i >= 0; --i) {
    bin[7 - i] = (val & (1 << i)) ? '1' : '0'; // Goes through each bit

    // Ex: i = 1
    // bin[6] = val & (1 << 2) ->
    // bin[6] = val & 0x02
    // if bit at that point returns true
  }
  bin[8] = '\0'; // Null ends the string

  /* bin += '\0'; */

  return bin;
};

char cCharHexSelector(const unsigned char nibble, const unsigned char bit) {
  // if bit == 0; lower nibble
  // if bit == 1; upper nibble

  unsigned char resultNibble = (bit) ? nibble & 0x0F : (nibble >> 4) & 0x0F;
  // If lesser than 10, you start at zero
  // if greater than 10, you start at A, then remove 10 to account for the
  // increase
  return (resultNibble < 10) ? '0' + resultNibble : 'A' + (resultNibble - 10);
};

char cIntHexSelector(const unsigned int val, const unsigned char index) {
  // Extract nibble at given index
  unsigned int nibble = (val >> (index * 4)) &
                        0x0F; // Shifts it all the way to the right
                              // Then masks to isolate the Right Most Nibble

  // Convert nibble into hex
  // if lesser than 10, output nibble literal
  // greater, start at 10 and set back the nibble by 10
  //    Then do char multiplication
  return (nibble < 10) ? '0' + nibble : 'A' + (nibble - 10);
};
