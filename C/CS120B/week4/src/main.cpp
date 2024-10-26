#include "timerISR-Fixed.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void TimerISR() { TimerFlag = 1; }

unsigned int count = 0;

// unsigned char passcode[4] = {'u', 'd', 'l', 'r'};
unsigned char passcode[4] = {'l', 'l', 'l', 'l'};
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

// NOTE: Never used
void addToInputs(char dir) {
  if (count >= 4) {
    count = 0;
  }
  if (count == 0 || inputs[count - 1] != dir) {
    inputs[count] = dir;
    ++count;
  }
}

// Waits n amount of ticks
// Each tick is 1ms, 1 tick = 1 ms
void Wait(int ticks) {
  for (int i = 0; i < ticks; ++i) {
    while (!TimerFlag) {
    }
    TimerFlag = 0;
  }
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

void Rotate(bool cw, float degrees) {
  // NOTE: Multiplying by 0.73 roughly translate to degrees
  // This does lock up the system for a bit, but it's not too bad
  for (int i = 0; i < degrees * 0.73; ++i) {
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

  if (yAxis > 0.6) {
    outDir(1); // up, 1
    currentDirection = 'u';
  } else if (yAxis < 0.4) {
    outDir(2); // down, 2
    currentDirection = 'd';
  } else if (xAxis > 0.6) {
    outDir(4); // right, 4
    currentDirection = 'r';
  } else if (xAxis < 0.4) {
    outDir(3); // left, 3
    currentDirection = 'l';
  } else {
    outDir(0); // center
  }
}

enum states { WAIT, PRESS, AUTH } state;

void Tick() {
  JoystickTick();

  // State Transistions
  switch (state) {
  case WAIT:
    if (!isCenter()) {
      state = PRESS;
    }
    break;
  case PRESS:
    if (isCenter()) {
      ++count;
      if (count > 3) {
        inputs[count] = currentDirection; // save input
        count = 0;
        if (CheckInputs()) {
          Rotate(true, 90);
          state = WAIT;
        } else {
          BlinkLEDs(4000);
          state = WAIT;
        }
        return;
      }
      // addToInputs(currentDirection); // save input
      inputs[count - 1] = currentDirection; // save input
      state = WAIT;
    }

    break;
  case AUTH:
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
  case AUTH:
    if (CheckInputs()) {
      count = 0;
    } else if (!CheckInputs()) {
      BlinkLEDs(4000);
      count = 0;
      state = WAIT;
    }
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

  return 0;
}
