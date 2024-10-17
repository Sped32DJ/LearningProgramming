#include <avr/interrupt.h>
#include <avr/io.h>
#include <timerISR-Fixed.h>
#include <util/delay.h>

void TimerISR(void) { TimerFlag = 1; }

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
  return (b ? (x | (0x01 << k)) : (x & ~(0x01 << k)));
  //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
  return ((x & (0x01 << k)) != 0);
}

void ADC_init() {
  ADMUX = (1 << REFS0);
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // ADEN: setting this bit enables analog-to-digital conversion.
  // ADSC: setting this bit starts the first conversion.
  // ADATE: setting this bit enables auto-triggering. Since we are
  //        in Free Running Mode, a new conversion will trigger whenever
  //        the previous conversion completes.
}

unsigned int ADC_read(unsigned char chnl) {
  uint8_t low, high;

  ADMUX = (ADMUX & 0xF8) | (chnl & 7);
  ADCSRA |= 1 << ADSC;
  while ((ADCSRA >> ADSC) & 0x01) {
  }

  low = ADCL;
  high = ADCH;

  return ((high << 8) | low);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned char Button() { return GetBit(PINC, 5); }

// 7SEG layout:   abcdefg
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

// TODO: complete outNum()
void outNum(int num) {
  PORTB = nums[num] >> 1; // assigns bits 1-7 of nums(a-f)
  // Bitshift 1 to the right
  PORTD = SetBit(PORTD, 7,
                 nums[num] & 0x01); // assigns bit 0 of nums(g)
  // 7th pin is the middle segment
}

enum states { INIT, OFF, ON, DECREMENT } state;

void Tick() {

  // State Transistions
  // TODO: complete transitions
  switch (state) {

  case INIT:
    PORTD = SetBit(PORTD, 2, 1); // RGB Green (Must stay on)
    PORTD = SetBit(PORTD, 5, 1); // Turn off 7-segment
    state = OFF;
    break;

  case OFF:
    if (Button()) {
      state = ON;
    }
    break;

  case ON:
    if (Button()) {
      state = OFF;
    }
    if (Button()) {
      state = DECREMENT;
      count = mappedPoten;
    }
    break;
  case DECREMENT:
    if (count > 0) {
      state = DECREMENT;
    } else {
      state = OFF;
    }
    break;

  default:
    state = INIT;
    break;
  }

  // State Actions
  // TODO: complete transitions
  switch (state) {

  case INIT:
    break;

  case ON:
    // Read Potentiometer and display
    unsigned int adcVal = ADC_read(0); // Read from A0
    int mappedPoten = map(adcVal, 0, 1023, 0, 15);
    outNum(mappedPoten);
    // Debuggin, if in this state, Red turns off
    // PORTD = SetBit(PORTD, 3, 0); // RGB Red (Must stay on)
    PORTD = SetBit(PORTD, 5, 0);
    break;

  case OFF:
    PORTD = SetBit(PORTD, 5, 1); // turn off 7-segment
    PORTD = SetBit(PORTD, 2, 1); // RGB Green (Must stay on)
    break;
  case DECREMENT:
    outNum(count);
    --count;

  default:
    break;
  }
}

int main(void) {
  ADC_init(); // initializes the analog to digital converter

  // RGB LED + 7-seg's 'g' + Red LED
  DDRD = 0xFF;  // Set all pins output
  PORTD = 0x00; // Clear PORTD

  // 7-segment + pin4 of PortD
  DDRB = 0xFF; // PORTB as output
  PORTB = 0x00;

  // Button + Potentiometer
  DDRC = 0x00; // Set all PORTC to input
  PORTC = 0xFF;

  state = INIT;

  TimerSet(1000);
  TimerOn();
  // Debuggin
  // PORTD = SetBit(PORTD, 3, 1); // Red RGB
  // PORTD = SetBit(PORTD, 4, 1); // Red LED
  // PORTD = SetBit(PORTD, 5, 1); // 7-segment power; 1 = off, 0 = on
  // outNum(15);

  while (1) {

    Tick(); // Execute one synchSM tick
    while (!TimerFlag) {
    } // Wait for SM period
    TimerFlag = 0; // Lower flag
  }

  return 0;
}
