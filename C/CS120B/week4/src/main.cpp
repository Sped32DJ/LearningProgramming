#include "timerISR-Fixed.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void TimerISR() { TimerFlag = 1; }

// TODO: declare your global variables here

// TODO: for exercise 2 and 3, the initial
// passcode should be up, down, left, right
unsigned char passcode[4] = {'u', 'd', 'l', 'r'};

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

// directions[] and outDir() replaces nums[] and outNum() from previous
// exercise. they behave the same, the only difference is outDir() outputs 4
// direction and a neutral
// center, r, l, d, u
// I can probably make this a case statement for each input "c,r,l,d,u"
int directions[5] = {0b0000001, 0b0000101, 0b0110000, 0b0111101, 0b0011100};
// TODO: complete the array containg the values needed
// for the 7 segments for each of the 4 directions
// a  b  c  d  Actions  g
// TODO: display the direction to the 7-seg display. HINT: will be very similar
void outDir(int dir) {
  PORTD = directions[dir] << 1;
  // Bitshift twice
  PORTB = SetBit(PORTB, 0, directions[dir] & 0x01);
  // 8th pin is in the middle segment
  // NOTE: 9th pin is a period
  // I think it is wired for a reason
}

int phases[8] = {0b0001, 0b0011, 0b0010, 0b0110, 0b0100,
                 0b1100, 0b1000, 0b1001}; // 8 phases of the stepper motor step

bool Button() { return GetBit(PINC, 4); }

float GetAxis(char port) {
  float raw = ADC_read(port);
  return (raw / 1023.0);
}

void JoystickTick() {
  float xAxis = GetAxis(2);
  float yAxis = GetAxis(3);

  if (yAxis > 0.6) {
    outDir(1); // up, 1
  } else if (yAxis < 0.4) {
    outDir(2); // down, 2
  } else if (xAxis > 0.6) {
    outDir(4); // right, 4
  } else if (xAxis < 0.4) {
    outDir(3); // left, 3
  } else {
    outDir(0); // center
  }
}
enum states { WAIT, PRESS } state; // TODO: finish the enum for the SM

void Tick() {

  // State Transistions
  // TODO: complete transitions
  switch (state) {
  case WAIT:
    break;
  case PRESS:
    break;
  default:
    state = WAIT;
    break;
  }

  // State Actions
  // TODO: complete Actions
  switch (state) {

  case WAIT:
    break;
  case PRESS:
    break;
  default:
    state = WAIT;
    break;
  }
}

int main(void) {
  // TODO: initialize all outputs and inputs

  ADC_init(); // initializes the analog to digital converter

  // Stepper Motor + 2 pins of 7 segment
  DDRB = 0xFF; // PORTB as output
  PORTB = 0x00;

  // Joystick + 2 LED's
  DDRC = 0x00;  // Last two bits are output, rest input
  PORTC = 0xFF; // All put last two pins are output

  // majority of 7 of segmenet (just bit shift later on)
  DDRD = 0xFF;  // Set all pins output
  PORTD = 0x00; // Clear PORTD

  state = WAIT;

  TimerSet(1); // period of 1 ms. good period for the stepper mottor
  TimerOn();

  while (1) {
    JoystickTick();

    Tick(); // Execute one synchSM tick
    while (!TimerFlag) {
    } // Wait for SM period
    TimerFlag = 0; // Lower flag
  }

  return 0;
}
