#include <avr/io.h>
#include <util/delay.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
  return ((x & (0x01 << k)) != 0);
}

unsigned char SetBit(unsigned char x, unsigned k, unsigned char b) {
  return (b ? (x | (0x01 << k)) : (x & ~(0x01 << k)));
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

unsigned char count = 0;

// Does this do 7-seg and LED
void outNum(int num) {
 // PORTD = nums[num] << 1; // assigns bits 1-7 of nums(a-f) to pins 2-7 of port d
  //PORTB = SetBit(PORTB, 0, nums[num] & 0x01);
}

// TODO  DDRB is the LED register
void outLED(int num) {
  PORTB = SetBit(PORTB, 2, num & 0x01); // LED 0
  PORTB = SetBit(PORTB, 3, num & 0x02); // LED 1
  PORTB = SetBit(PORTB, 4, num & 0x04); // LED 2
  PORTB = SetBit(PORTB, 5, num & 0x08); // LED 3
}

unsigned char Button() { return GetBit(PINC, 4); }

unsigned char Reset() { return GetBit(PINC, 5); }

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
    if (Button()) {
        state = INCREMENT;
    }
    break;

  case START:
    if (Reset() || count > 15) {
      state = INIT;
    } else if (Button()) {
      state = INCREMENT;
    }
    break;

  case INCREMENT:
    if (Reset()) {
      state = INIT;
    } else if (Button()) {
      if (count < 16) {
        ++count;
      } else {
	state = INIT;
      }
      state = START;
    }

    break;
  default:
    state = INIT;
    break;
  }
  // State Actions
  // TODO: Complete Actions
  switch (state) {
  case INIT:
    count = 0;
    outNum(count);
    outLED(count);
    break;

  case START:
    outNum(count);
    outLED(count);
    break;

  case INCREMENT:
    outNum(count);
    outLED(count);
    break;

  default:
    break;
  }
}

int main(void) {
  // 7-segment display (PORTD)
  DDRD = 0xFF;  // Set all pins output
  PORTD = 0x00; // Clear PORTD

  // LEDs (PORTB)
  DDRB = 0xFF; // PORTB as output
  PORTB = 0x00;

  // Buttons
  DDRC = 0x00; // Set all PORTC to input
  PORTC = 0xFF;
  /* // Buttons (A4 and A5)
  DDRC &= ~(1 << DDC4);   // Set A4 (PC4) as input
  DDRC &= ~(1 << DDC5);   // Set A5 (PC5) as input
  PORTC |= (1 << PORTC4); // Enable pull-up resistor on A4
  PORTC |= (1 << PORTC5); // Enable pull-up resistor on A5 */

  state = INIT;
  count = 0x01;
  // 1,7, B,D is bad

  while (1) {
    Tick(); // Execute one SM tick
    _delay_ms(100);
  }

  return 0;
}
