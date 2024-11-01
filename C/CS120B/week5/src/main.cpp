#include "helper.h"
#include "periph.h"
#include "timerISR.h"

// TODO: Change this depending on which exercise you are doing.
// Exercise 1: 3 tasks
// Exercise 2: 5 tasks
// Exercise 3: 7 tasks
#define NUM_TASKS 3

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 1;
const unsigned long SNAR_PERIOD = 1000;
const unsigned long DISP_PERIOD = 1;
const unsigned long LEFT_PERIOD = 200;
task tasks[NUM_TASKS]; // declared task array with NUM_TASKS amount of tasks

// TODO: Define, for each task:
//  (1) enums and
//  (2) tick functions
enum SNAR_States { SonarInit, SONAR_S1 };
volatile unsigned int in_distance = 0;
volatile unsigned int cm_distance = 0;

enum DISP_States { displayInit, disp_S1, disp_S2, disp_S3, disp_S4 };
bool isInches = false; // default metric (yucky); true = imperial

enum Left_States { leftInit, Left_S1, Left_S2 };
unsigned char LeftButton() { return !GetBit(PINC, 1); }

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

// Tick Functions
int sonar_TickFct(int state) {
  // Transitions
  switch (state) {
  case SonarInit:
    state = SONAR_S1;
    break;
  case SONAR_S1:
    state = SONAR_S1;
    break;
  }

  // State Actions
  switch (state) {
  case SONAR_S1:
    // sonar_read() outputs cm by default + .50 rounding
    in_distance = int(sonar_read() / 2.54 + 0.50);
    cm_distance = int(sonar_read() + 0.50);
    // NOTE: Hopefully this works soon
    serial_println(in_distance);
    break;
  }
  return state;
}

int display_TickFct(int state) {
  // Transitions
  switch (state) {
  case displayInit:
    state = disp_S1;
    break;

    // Transitions into each of the 4 digits
  case disp_S1:
    state = disp_S2;
    break;
  case disp_S2:
    state = disp_S3;
    break;
  case disp_S3:
    state = disp_S4;
    break;
  case disp_S4:
    state = disp_S1;
    break;
  }

  // Actions
  switch (state) {
  case displayInit:
    break;
  case disp_S1:
    // Goes left to right
    outNum(((((isInches) ? in_distance : cm_distance)) / 1000) % 10);
    // D# ports are active low..
    PORTB = (PORTB & 0xC3) | 0x1C; // Enable active low left most digit
    break;
  case disp_S2:
    outNum(((((isInches) ? in_distance : cm_distance)) / 100) % 10);
    PORTB = (PORTB & 0xC3) | 0x2C;
    break;
  case disp_S3:
    outNum(((((isInches) ? in_distance : cm_distance)) / 10) % 10);
    PORTB = (PORTB & 0xC3) | 0x34;
    break;
  case disp_S4:
    outNum((((isInches) ? in_distance : cm_distance)) % 10);
    PORTB = (PORTB & 0xC3) | 0x38; // Enable active low right most digit
    break;
  default:
    break;
  }
  return state;
}
// Only two states, should technically work perfectly
// NOTE: If fucked, make 4 states
int left_TckFct(int state) {
  // Transitions
  switch (state) {
  case leftInit:
    state = Left_S1;
    break;
  case Left_S1:
    if (LeftButton()) {
      state = Left_S2;
    }
    break;
  case Left_S2:
    if (!LeftButton()) {
      state = Left_S1;
      // During release transition, it flips the bit
      isInches = !isInches;
    }
    break;
  }

  // Action States
  switch (state) {
  case leftInit:
    break;
  case Left_S1:
    break;
  case Left_S2:
    break;
  }
  return state;
}

int main(void) {
  DDRD = 0xFF;
  PORTD = 0x00;

  DDRB = 0xFF;
  PORTB = 0x00; // The one bit for input (last bit trig; rewired)

  DDRC = 0xF8; // 2 button pins + echo input (rewired), then 3 pins left for RGB
  PORTC = 0x07;

  ADC_init();        // initializes ADC
  sonar_init();      // initializes sonar
  serial_init(9600); // Helps debugging

  // TODO: Initialize tasks here
  //  e.g. tasks[0].period = TASK1_PERIOD
  //  tasks[0].state = ...
  //  tasks[0].elapsedTime = ...
  //  tasks[0].TickFct = &task1_tick_function;
  task tasks[]{{SonarInit, SNAR_PERIOD, tasks[0].period, &sonar_TickFct},
               {displayInit, DISP_PERIOD, tasks[1].period, &display_TickFct},
               {leftInit, LEFT_PERIOD, tasks[2].period, &left_TckFct}};
  TimerSet(GCD_PERIOD);
  TimerOn();

  while (1) {
  }

  return 0;
}
