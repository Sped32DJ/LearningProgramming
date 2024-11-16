#include "helper.h"
#include "periph.h"
#include "timerISR.h"

#define NUM_TASKS 7 // TODO: Change to the number of tasks being used

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 1; // TODO:Set the GCD Period

const unsigned long LBUTTON_PERIOD = 100;
const unsigned long RGB_PERIOD = 150;
const unsigned long JOY_PERIOD = 100;
const unsigned long BZR_PERIOD = 400;
const unsigned long RBUTTON_PERIOD = 100;
const unsigned long STEPPER_PERIOD = 1;
const unsigned long SERVO_PERIOD = 1;

task tasks[NUM_TASKS]; // declared task array with 5 tasks

// TODO: Declare your tasks' function and their states here
enum LBUTTON_STATES { LB_IDLE, LB_HOLD };
enum RGB_STATES { RGB_IDLE, AMBER, PURSUIT };
enum JOY_STATES { JOY_IDLE, JOY_HOLD };
enum BZR_STATES { BZR_IDLE, BZR_ON };
enum RBUTTON_STATES { RB_IDLE, RB_HOLD };
enum STEPPER_STATES { STEPPER_IDLE };
enum SERVO_STATES { SERVO_IDLE };

// Helper Functions
bool JButton() { return !GetBit(PINC, 2); }
bool LButton() { return GetBit(PINC, 3); }
bool RButton() { return !GetBit(PINC, 4); }

// Helper variables
bool pursuitMode = false;
bool amberMode = false;

unsigned char buzzMode = 0; // BuzzMode toggle
unsigned char highBuzz = 0;

unsigned int LBcount = 0;

int stages[8] = {0b0001, 0b0011, 0b0010, 0b0110,
                 0b0100, 0b1100, 0b1000, 0b1001}; // Stepper motor phases

int xAxis = 0.0;
int yAxis = 0;
void JoystickTick() {
  yAxis = ADC_read(0);
  xAxis = ADC_read(1);
}

// TODO: Implement PWM
int LButton_Tick(int state) {
  switch (state) {
  case LB_IDLE:
    if (LButton()) {
      state = LB_HOLD;
    }
    break;
  case LB_HOLD:
    if (!LButton()) {
      // Only gos into pursuitMode after 1 second (3 ticks;
      // NOTE: 10 ticks are not 1 second... idk why)
      if (LBcount >= 3) {
        pursuitMode = 1;
        amberMode = !pursuitMode;
      } else {
        amberMode = 1;
        pursuitMode = !amberMode;
      }
      state = LB_IDLE;
    } else if (LButton()) {
      state = LB_HOLD;
    }
    break;
  }
  switch (state) {
  case LB_IDLE:
    // DEBUGGING:
    // PORTD &= 0xDF; // 0's out Right RED
    LBcount = 0;
    break;
  case LB_HOLD:
    // DEBUGGING:
    // PORTD |= 0x20; // Right RED
    ++LBcount;
    break;
  }

  return state;
}

unsigned int RGBcount = 0;
int RGBTick(int state) {
  switch (state) {
  case RGB_IDLE:
    if (pursuitMode) {
      state = PURSUIT;
    } else if (amberMode) {
      state = AMBER;
    } else {
      state = RGB_IDLE;
    }
    break;
  case AMBER:
    if (pursuitMode) {
      buzzMode = 0;
      state = PURSUIT;
    } else if (amberMode) {
      state = AMBER;
    } else {
      state = RGB_IDLE;
    }
    break;
  case PURSUIT:
    if (pursuitMode) {
      state = PURSUIT;
    } else if (amberMode) {
      state = AMBER;
    } else {
      state = RGB_IDLE;
    }
    break;
  }

  unsigned char flash = 0;
  switch (state) {
  case RGB_IDLE:
    PORTD &= 0xE3; // 0's out RGB
    break;
  case AMBER:
    // TODO: Use PWM to amber color
    // PORTD = (PORTD & ~0x1C) | 0x18;
    flash = !flash;
    if (RGBcount & 0x01) {
      TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));
      PORTD &= 0xE3; // 0's out RGB
    } else if (RGBcount <= 5) {
      PORTD = (PORTD & ~0x1C);
      PORTD |= (1 << PD4);
      PORTD |= (1 << PD3);
      // Configure PWM for PD3 (Green)
    } else {
      RGBcount = 0;
    }
    ++RGBcount;

    break;
  case PURSUIT:
    // TODO: Actually does the two flashes
    // This actually enabled on a single press
    // PORTD &= 0xE3; // 0's out RGB
    //
    // Disable PWM on PD3 by clearing the COM2B1 and COM2B0 bits
    TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));

    // NOTE: Turns purple sometimes
    if (RGBcount & 0x01) {
      PORTD &= 0xE3; // 0's out RGB
    } else if (RGBcount <= 5) {
      PORTD &= 0xE3; // 0's out RGB
      PORTD |= 0x04; // Blue
    } else if (RGBcount <= 9) {
      PORTD &= 0xE3; // 0's out RGB
      PORTD |= 0x10; // Red
    } else {
      RGBcount = 0;
    }
    ++RGBcount;
    break;
  }
  return state;
}

// NOTE: Not sure what to do with this
// Maybe do modifications based upon the inputs
int JOYTick(int state) {
  JoystickTick(); // This does all the reading

  switch (state) {
  case JOY_IDLE:
    if (JButton()) {
      state = JOY_HOLD;
    }
    break;
  case JOY_HOLD:
    if (!JButton()) {
      state = JOY_IDLE;
      if (pursuitMode) {
        buzzMode = !buzzMode;
      }
      highBuzz = 1;
    }
    break;
  }
  switch (state) {
  case JOY_IDLE:
    break;
  case JOY_HOLD:
    break;
  }
  return state;
}

int BuzzerTick(int state) {
  switch (state) {
  case BZR_IDLE:
    if (buzzMode && pursuitMode) {
      state = BZR_ON;
    }
    break;
  case BZR_ON:
    if (!buzzMode || !pursuitMode) {
      state = BZR_IDLE;
    } else {
      OCR0A = 128; // Turn on buzzer
      state = BZR_ON;
    }
    break;
  }
  switch (state) {
  case BZR_IDLE:
    // Turn off PWM and clear PD6
    TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
    PORTD &= ~(1 << PD6);
    OCR0A = 255; // Turn off buzzer

    break;
  case BZR_ON:
    TCCR0A |= (1 << COM0A1) | (1 << WGM00); // Fast PWM, non-inverting mode
    TCCR0B |= (1 << CS01);                  // Set prescaler to 8

    // Alternate between high and low notes
    if (highBuzz) {
      TCCR0B = (TCCR0B & 0xF8) | 0x05; // Prescaler to 1024
    } else {
      TCCR0B = (TCCR0B & 0xF8) | 0x03; // prescaler to 8
    }
    highBuzz = !highBuzz;
    break;
  }
  return state;
}

unsigned char reverse = 0;
int RB_Tick(int state) {
  switch (state) {
  case RB_IDLE:
    if (RButton()) {
      state = RB_HOLD;
    }
    break;
  case RB_HOLD:
    if (!RButton()) {
      reverse = !reverse;
      if (reverse) {
        PORTD |= 0x20; // Right RED
      } else {
        PORTD &= 0xDF; // 0's out Right RED
      }
      state = RB_IDLE;
    }
    break;
  }
  switch (state) {
  case RB_IDLE:
    break;
  case RB_HOLD:
    break;
  }
  return state;
}

// bool reverse
// float stepperSpeed - ->> 0.0 - 100.0
int stepCount = 0;
int phase = 0;
int period = 0;
int StepperTick(int state) {
  switch (state) {
  case STEPPER_IDLE:
    if (yAxis > 570) {
      period = map(yAxis, 570, 1023, 1, 5);
      if (stepCount % (6 - period) == 0) {
        PORTB = (PORTB & 0x03) | stages[phase] << 2;
        if (reverse) {
          phase = (phase < 0) ? 7 : --phase;
        } else {
          phase = (phase > 7) ? 0 : ++phase;
        }
      }
      // Iterates counter and prevents overflow
      stepCount = (stepCount > 500) ? 0 : ++stepCount;
    }
    break;
  }

  switch (state) {
  case STEPPER_IDLE:
    state = STEPPER_IDLE;
    break;
  }
  return state;
}

int ServoTick(int state) {
  switch (state) {
  case SERVO_IDLE:
    int servoPos = map(xAxis, 0, 1023, 5000, 1000);
    OCR1A = servoPos;
    break;
  }
  switch (state) {
  case SERVO_IDLE:
    state = SERVO_IDLE;
    break;
  }
  return state;
}

void TimerISR() {
  for (unsigned int i = 0; i < NUM_TASKS;
       i++) { // Iterate through each task in the task array
    if (tasks[i].elapsedTime ==
        tasks[i].period) { // Check if the task is ready to tick
      tasks[i].state = tasks[i].TickFct(
          tasks[i].state);      // Tick and set the next state for this task
      tasks[i].elapsedTime = 0; // Reset the elapsed time for the next tick
    }
    tasks[i].elapsedTime +=
        GCD_PERIOD; // Increment the elapsed time by GCD_PERIOD
  }
}

// TODO: Create your tick functions for each task

int main(void) {
  // TODO: initialize all your inputs and ouputs
  DDRB = 0xFF;
  PORTB = 0x00;

  // All inputs PORTC
  DDRC = 0x00;
  PORTC = 0xFF;

  DDRD = 0xFF;
  PORTD = 0x00;

  ADC_init(); // initializes ADC

  // TODO: Initialize the buzzer timer/pwm(timer0)
  TCCR0A =
      (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, non-inverting
  TCCR0B = (1 << CS01);                            // Prescaler = 8
  OCR0A = 0; // Start with 0 duty cycle (off)

  // TODO: Initialize the servo timer/pwm(timer1)
  TCCR1A = (1 << WGM11) | (1 << COM1A1);              // Fast PWM, non-inverting
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Mode 14, Prescaler = 8
  ICR1 = 39999;                                       // TOP value for 50 Hz
  OCR1A = 2999; // Neutral position (1.5 ms pulse width)

  // TODO: Initialize tasks here
  //  e.g.
  //  tasks[0].period = ;
  //  tasks[0].state = ;
  //  tasks[0].elapsedTime = ;
  //  tasks[0].TickFct = ;
  tasks[0].period = LBUTTON_PERIOD;
  tasks[0].state = LB_IDLE;
  tasks[0].elapsedTime = tasks[0].period;
  tasks[0].TickFct = &LButton_Tick;

  tasks[1].period = RGB_PERIOD;
  tasks[1].state = RGB_IDLE;
  tasks[1].elapsedTime = tasks[1].period;
  tasks[1].TickFct = &RGBTick;

  tasks[2].period = JOY_PERIOD;
  tasks[2].state = JOY_IDLE;
  tasks[2].elapsedTime = tasks[2].period;
  tasks[2].TickFct = &JOYTick;

  tasks[3].period = BZR_PERIOD;
  tasks[3].state = BZR_IDLE;
  tasks[3].elapsedTime = tasks[3].period;
  tasks[3].TickFct = &BuzzerTick;

  tasks[4].period = RBUTTON_PERIOD;
  tasks[4].state = RB_IDLE;
  tasks[4].elapsedTime = tasks[4].period;
  tasks[4].TickFct = &RB_Tick;

  tasks[5].period = STEPPER_PERIOD;
  tasks[5].state = STEPPER_IDLE;
  tasks[5].elapsedTime = tasks[5].period;
  tasks[5].TickFct = &StepperTick;

  tasks[6].period = SERVO_PERIOD;
  tasks[6].state = SERVO_IDLE;
  tasks[6].elapsedTime = tasks[6].period;
  tasks[6].TickFct = &ServoTick;

  TimerSet(GCD_PERIOD);
  TimerOn();

  while (1) {
    // PORTD |= 0x10; // RED
    // PORTD |= 0x08; // GREEN
    // PORTD |= 0x04; // BLUE
    // PORTD |= 0x20; // Right RED
  }

  return 0;
}
