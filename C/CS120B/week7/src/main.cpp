#include "helper.h"
#include "periph.h"
#include "timerISR.h"

#define NUM_TASKS 3 // TODO: Change to the number of tasks being used

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 100; // TODO:Set the GCD Period

const unsigned long LBUTTON_PERIOD = 100;
const unsigned long RGB_PERIOD = 100;
const unsigned long JOY_PERIOD = 100;
const unsigned long BZR_PERIOD = 100;

task tasks[NUM_TASKS]; // declared task array with 5 tasks

// TODO: Declare your tasks' function and their states here
enum LBUTTON_STATES { LB_IDLE, LB_HOLD };
enum RGB_STATES { RGB_IDLE, AMBER, PURSUIT };
enum JOY_STATES { JOY_READ };

// Helper Functions
bool JButton() { return !GetBit(PINC, 2); }
bool LButton() { return !GetBit(PINC, 3); }
bool RButton() { return !GetBit(PINC, 4); }

// Helper variables
bool pursuitMode = false;
bool amberMode = false;

unsigned int LBcount = 0;

// Joystick helper functions
float GetAxis(char port) {
  float raw = ADC_read(port);
  return (raw / 1024.0);
}

unsigned char currentDirection = 0;
void JoystickTick() {
  float xAxis = GetAxis(0);
  float yAxis = GetAxis(1);

  // Do upper case for extended
  if (xAxis > 0.6) {
    currentDirection = 'r';
  } else if (xAxis < 0.4) {
    currentDirection = 'l';
  } else if (yAxis > 0.6) {
    currentDirection = 'u';
  } else if (yAxis < 0.4) {
    currentDirection = 'd';
  } else {
    // NOTE: Remove if you want to save last
    currentDirection = 'c';
  }
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
      // Only gos into pursuitMode after 1 second
      if (LBcount >= 10) {
        pursuitMode = !pursuitMode;
        amberMode = false;
      } else {
        amberMode = !amberMode;
        pursuitMode = false;
      }
      state = LB_IDLE;
    } else {
      state = LB_HOLD;
    }
    break;
  }
  switch (state) {
  case LB_HOLD:
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
  switch (state) {
  case RGB_IDLE:
    PORTD &= 0xE3; // 0's out RGB
    break;
  case AMBER:
    // TODO: Use PWM to amber color
    PORTD = (PORTD & 0b11100111) | 0b00011000;
    break;
  case PURSUIT:
    PORTD &= 0xE3; // 0's out RGB
    if (RGBcount & 0x01) {
      PORTD &= 0xE3; // 0's out RGB
    } else if (RGBcount <= 6) {
      PORTD &= 0xF3; // 0-out G&B
      PORTD |= 0x04;
    } else if (RGBcount <= 12) {
      PORTD &= 0xE7; // 0-Out R&G
      PORTD |= 0x10; // Blue
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
  case JOY_READ:
    break;
  }
  switch (state) {
  case JOY_READ:
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

int stages[8] = {0b0001, 0b0011, 0b0010, 0b0110,
                 0b0100, 0b1100, 0b1000, 0b1001}; // Stepper motor phases

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

  // TODO: Initialize the servo timer/pwm(timer1)

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
  tasks[2].state = JOY_READ;
  tasks[2].elapsedTime = tasks[2].period;
  tasks[2].TickFct = &JOYTick;

  TimerSet(GCD_PERIOD);
  TimerOn();

  while (1) {
  }

  return 0;
}
