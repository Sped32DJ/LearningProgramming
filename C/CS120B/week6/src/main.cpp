#include "LCD.h"
#include "helper.h"
#include "periph.h"
#include "timerISR.h"

// TODO: declare variables for cross-task communication

/* TODO: match with how many tasks you have */
#define NUM_TASKS 0

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 100; /* TODO: Calulate GCD of tasks */
const unsigned long BUTTON_PERIOD = 500;
const unsigned long ADC_PERIOD = 100;
const unsigned long BUZZER_PERIOD = 2;
const unsigned long LCD_PERIOD = 100;
const unsigned long THERMISTER_PERIOD = 100;

task tasks[NUM_TASKS]; // declared task array with 5 tasks

// States
enum Button_States { IDLE, HOLD };
enum ADC_States { ADC_INIT, ADC_READ };
enum Buzzer_States { BUZZER_INIT, BUZZER_ON, BUZZER_OFF };
enum LCD_States { LCD_INIT, LCD_WRITE };
enum Thermister_States { THERMISTER_INIT, THERMISTER_READ };

// Button SM
unsigned char Button() { return !GetBit(PINC, 1); }
bool forceStop = false;
int ButtonTick(int state) {
  switch (state) {
  case IDLE:
    if (Button()) {
      state = HOLD;
    }
    break;
  case HOLD:
    if (!Button()) {
      state = IDLE;
      forceStop = forceStop ? false : true;
    }
    break;
  default:
    state = IDLE;
    break;
  }
  return state;
}

// ADC-Potentiometer SM
int ADC_Tick(int state) {
  unsigned short adcValue = map(ADC_read(0), 0, 1023, 0, 15);
  switch (state) {
  case ADC_INIT:
    state = ADC_READ;
    break;
  case ADC_READ:
    state = ADC_READ;
    break;
  default:
    state = ADC_INIT;
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

int main(void) {
  // TODO: initialize all your inputs and ouputs
  DDRB = 0xFF;
  PORTB = 0x00;

  // All inputs
  DDRC = 0x00;
  PORTC = 0xFF;

  DDRD = 0xFF;
  PORTD = 0x00;

  ADC_init(); // initializes ADC

  // TODO: Initialize tasks here
  //  e.g. tasks[0].period = TASK1_PERIOD
  //  tasks[0].state = ...
  //  tasks[0].elapsedTime = ...
  //  tasks[0].TickFct = &task1_tick_function;

  TimerSet(GCD_PERIOD);
  TimerOn();

  while (1) {
  }

  return 0;
}

// Feel free to implement your tasks' tick functions under here
