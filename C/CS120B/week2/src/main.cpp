#include <avr/io.h>
#include <serialATmega.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
  return ((x & (0x01 << k)) != 0);
}

int nums[16] = {
    0b1111110, // 0
    0b0110000, // 1
    0b1101101, // 2
    0b1111001, // 3
    0b0110011, // 4
    0b1011011, // 5
    0b1011111, // 6
    0b1110000, // 7
    0b1111111, // 8
    0b1111011, // 9
    0b1110111, // a
    0b0011111, // b
    0b1001110, // c
    0b0111101, // d
    0b1001111, // e
    0b1000111  // f
};

int count = 0;

// Does this do 7-seg and LED
void outNum(int num) {
  PORTD = nums[num] << 1; // assigns bits 1-7 of nums(a-f) to pins 2-7 of port d
  PORTB =
      SetBit(PORTB, 0,
             nums[num] & 0x01); // assigns bit 0 of nums(g) to pin 0 of port b
}

// TODO  How to detect the RESET button?
// Not sure if I can just A0 and A1
unsigned char Reset() { return (DDRB >> 4) & 0x01; }

unsigned char Button() { return (DDRB >> 5) & 0x01; }

enum states {
  INIT,
  START,
  INCREMENT
} state; // TODO: finish the enum for the SM

void Tick() {
  // State Transistions
  // TODO: complete transitions
  switch (state) {
  case INIT:
    // TODO  Make this the off stage (Do I need to?)
    count = 0;
    outNum(count);
    break;
  case START:
    (RESET || count > 14) ? state = START : ++count;
    break;
  case INCREMENT:
    // TODO Declare the RESET button
    // make sure count > 14 is valid
    (RESET || count > 14) ? state = START : ++count;
    break;

  default:
    state = INIT;
    break;
  }
  // State Actions
  // TODO: Complete Actions
  switch (state) {
  case INIT:
    RESET = 0x0;
    count = 0x0;
    outNum(count);
    break;
  case START:
    RESET = 0x0;
    count = 0x0;
    outNum(count);
    break;
  case INCREMENT:
    outNum(count);
    break;
  default:
    state = START;
    break;
  }
}
int main(void) {
  // TODO: initialize all outputs and inputs
  // TODO: initialize your state
  DDRD = 0xFF; // Data Direction Register, 7-segment
  DDRC = 0x00; // LEDs
  DDRB = 0x00; // Buttons

  /* states STATE = INIT; */
  /* FFRB = 0x00; */

  while (1) {
    Tick(); // Execute one SM tick
  }

  return 0;
}

/* int main(void) {
  while (1) {
    if ((PINB >> 2) & 0x01) {
      PORTD = PORTD | 0x08;
    } else {
      PORTD = PORTD & 0x07;
    }
  }
  return 0;
} */
