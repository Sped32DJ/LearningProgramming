#include "timerISR-Fixed.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void TimerISR() { TimerFlag = 1; }

unsigned int count = 0;
unsigned int timesUnlocked = 0;
bool overwriting = 0;

// unsigned char passcode[4] = {'u', 'd', 'l', 'r'};
unsigned char passcode[4] = {'u', 'd', 'l', 'r'};
unsigned char inputs[4] = {0, 0, 0, 0};
unsigned char currentDirection = 0;

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

// Order: c, r, l, d, u
int directions[5] = {0b0000001, 0b0000101, 0b0110000, 0b0111101, 0b0011100};

void outDir(int dir) {
  PORTD = directions[dir] << 1;
  // Bitshift twice
  PORTB = SetBit(PORTB, 0, directions[dir] & 0x01);
  // 8th pin is in the middle segment
  // NOTE: 9th pin is a period
}

void outLED(int num) {
  PORTC = SetBit(PORTC, 0, num & 0x01); // LED 0
  PORTC = SetBit(PORTC, 1, num & 0x02); // LED 1
}

int phases[8] = {0b0001, 0b0011, 0b0010, 0b0110, 0b0100,
                 0b1100, 0b1000, 0b1001}; // 8 phases of the stepper motor step

bool Button() { return GetBit(PINC, 4); }

float GetAxis(char port) {
  float raw = ADC_read(port);
  return (raw / 1024.0);
}

// on is basically a bool that turns LEDs on or off
void SetLEDs(unsigned char on) {
  PORTC = SetBit(PORTC, 0, on);
  PORTC = SetBit(PORTC, 1, on);
}

void BlinkLEDs(int ms) {
  for (int i = 0; i < ms; ++i) {
    if (!(i / 1000 % 2)) {
      SetLEDs(0);
    } else {
      SetLEDs(1);
    }
    while (!TimerFlag) {
    }
    TimerFlag = 0;
  }
}

bool isCenter() {
  return (GetAxis(2) < 0.6 && GetAxis(2) > 0.3) &&
         (GetAxis(3) < 0.6 && GetAxis(3) > 0.3);
}

bool CheckInputs() {
  for (int i = 0; i < 4; ++i) {
    if (inputs[i] != passcode[i]) {
      return false;
    }
  }
  return true;
}

void Rotate(bool cw, float quarter) {
  // A full rotation is 512 steps
  // quarter = 128
  for (int i = 0; i < quarter * 128; ++i) {
    if (cw) {
      for (int i = 0; i < 8; ++i) {
        // Clears out 4 motor output pins and adds new phase
        PORTB = (PORTB & 0xC3) | phases[i] << 2;
        while (!TimerFlag) {
        }
        TimerFlag = 0;
      }
    } else {
      for (int i = 7; i >= 0; --i) {
        // Clears out 4 motor output pins and adds new phase
        PORTB = (PORTB & 0xC3) | phases[i] << 2;
        while (!TimerFlag) {
        }
        TimerFlag = 0;
      }
    }
  }
}

void JoystickTick() {
  float xAxis = GetAxis(2);
  float yAxis = GetAxis(3);

  if (yAxis > 0.6) { // Actually 'r'
    outDir(1);       // up, 1
    currentDirection = 'r';
  } else if (yAxis < 0.4) { // Actually 'l'
    outDir(2);              // down, 2
    currentDirection = 'l';
  } else if (xAxis > 0.6) { // Actually 'u'
    outDir(4);              // right, 4,
    currentDirection = 'u';
  } else if (xAxis < 0.4) { // Actually 'd'
    outDir(3);              // left, 3
    currentDirection = 'd';
  } else {
    outDir(0); // center
  }
}

enum states { WAIT, PRESS, OVERWRITE } state;

void Tick() {
  JoystickTick();

  // State Transistions
  switch (state) {
  case WAIT:
    if (!isCenter()) {
      state = PRESS;
    } else if (!Button() && timesUnlocked % 2 != 0) {
      state = OVERWRITE;
    } else {
      state = WAIT;
    }

    break;
  case OVERWRITE:
    if (Button()) {
      state = WAIT;
    }
    break;
  case PRESS:
    if (isCenter()) {
      inputs[count] = currentDirection; // save input

      // Overwriting mode
      if (overwriting) {
        passcode[count] = currentDirection;
      }

      if (count == 3) {
        count = 0;
        outDir(count);
        if (CheckInputs()) {
          ++timesUnlocked;
          overwriting = 0;
          PORTB = (PORTB & 0xCD) | 0x00; // turn off decimal
          if (timesUnlocked % 2 == 0) {
            Rotate(false, 1);
          } else {
            Rotate(true, 1);
          }
        } else {
          BlinkLEDs(4000);
        }
        state = WAIT;
        return;
      }

      ++count;
      state = WAIT;
    }

    break;
  default:
    state = WAIT;
    break;
  }

  // State Actions
  switch (state) {

  case WAIT:
    outLED(count);
    break;
  case PRESS:
    break;
  case OVERWRITE:
    count = 0;
    overwriting = 1;
    PORTB = (PORTB & 0xCD) | 0x02; // Turn on decimal
    break;
  default:
    state = WAIT;
    break;
  }
}

int main(void) {
  ADC_init(); // initializes the analog to digital converter

  // Stepper Motor + 2 pins of 7 segment
  DDRB = 0xFF; // PORTB as output
  PORTB = 0x00;

  // Joystick + 2 LED's
  DDRC = 0x03;   // Last two bits are output, rest input
  PORTC = ~0x03; // All put last two pins are output

  // majority of 7 of segmenet (just bit shift later on)
  DDRD = 0xFF;  // Set all pins output
  PORTD = 0x00; // Clear PORTD

  state = WAIT;

  TimerSet(1); // period of 1 ms. good period for the stepper mottor
  TimerOn();

  while (1) {
    Tick(); // Execute one synchSM tick
    while (!TimerFlag) {
    } // Wait for SM period
    TimerFlag = 0; // Lower flag
  }
}
