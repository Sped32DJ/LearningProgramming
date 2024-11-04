#include "LCD.h"
#include "helper.h"
#include "periph.h"
#include "timerISR.h"
#include <stdio.h>

// TODO: declare variables for cross-task communication

/* TODO: match with how many tasks you have */
#define NUM_TASKS 5

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 1; /* TODO: Calulate GCD of tasks */
const unsigned long BUTTON_PERIOD = 500;
const unsigned long ADC_PERIOD = 100;
const unsigned long LCD_PERIOD = 500;
const unsigned long THERMISTER_PERIOD = 100;

const unsigned long BUZZER_PERIOD = 100;
const unsigned long BUZZER_PWM_PERIOD = 1000;

const unsigned long FAN_PERIOD = 1;
const unsigned long FAN_PWM_PERIOD = 10;

// PWM Values
// FAN PWM
unsigned short FPwmH = 0;
unsigned short FPwmL = 0;

// Buzzer PWM
unsigned short BPwmH = 0;
unsigned short BPwmL = 10;

task tasks[NUM_TASKS]; // declared task array with 5 tasks

// States
enum Button_States { IDLE, HOLD };
enum ADC_States { ADC_INIT, ADC_READ };
enum Buzzer_States { BUZZER_INIT, BUZZER_ON, BUZZER_OFF };
enum LCD_States { LCD_INIT, LCD_WRITE };
enum Thermister_States { THERMISTER_INIT, THERMISTER_READ };
enum Fan_States { FAN_INIT, FanH, FanL };

// Variables

// For button SM
bool forceStop = false;

// for ADC SM
// The range is 0-20 (21 unique vals), 0-9 rev, 10 idle, 11-20 forward
unsigned short adcValue = map(ADC_read(0), 0, 1023, 0, 20);

// Button SM
unsigned char Button() { return !GetBit(PINC, 1); }
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
// Display Off/on/testing states
int ADC_Tick(int state) {
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
  switch (state) {
  case ADC_READ:
    // The range is 0-20 (21 unique vals), 0-9 rev, 10 idle, 11-20 forward
    adcValue = map(ADC_read(0), 0, 1023, 0, 20);
    if (adcValue >= 0 && adcValue <= 9 && !forceStop) {
      // TODO: Reverse polarity + make it dynamic
      FPwmL = adcValue;
      FPwmH = 10 - adcValue;
    } else if (adcValue == 10 || forceStop) {
      FPwmH = 0;
      FPwmL = 10;
    } else if (adcValue >= 11 && adcValue <= 20 && !forceStop) {
      FPwmH = adcValue - 10;
      FPwmL = 10 - (adcValue - 10);
    }

    break;
  }

  return state;
}

// Implement logic for buzzer to go off
unsigned short buzz = 0;
int BuzzerTick(int state) {
  switch (state) {
  case BUZZER_INIT:
    state = BUZZER_OFF;
    break;
  case BUZZER_ON:
    if (buzz < BPwmH) {
      state = BUZZER_ON;
    } else {
      state = BUZZER_OFF;
      buzz = 0;
    }
    break;
  case BUZZER_OFF:
    if (buzz < BPwmL) {
      state = BUZZER_OFF;
    } else {
      state = BUZZER_ON;
      buzz = 0;
    }
    break;
  default:
    state = BUZZER_INIT;
    break;
  }
  switch (state) {
  case BUZZER_ON:
    PORTB |= 0x01;
    break;
  case BUZZER_OFF:
    PORTB &= 0xFE;
    break;
  }
  return state;
}

// TODO: Implement LCD Tick function
// This one is all new to me
// Implement logic for LCD to display the ADC value
// Implement the boolean logic for the button press
int LCD_Tick(int state) {
  static char buffer1[16];
  static char buffer2[16];

  switch (state) {
  case LCD_INIT:
    state = LCD_WRITE;
    break;
  case LCD_WRITE:
    state = LCD_WRITE;
    break;
  default:
    state = LCD_INIT;
    break;
  }
  switch (state) {
  case LCD_WRITE:
    if (forceStop) {
      sprintf(buffer1, "Sys: off");
    } else {
      sprintf(buffer1, "Sys: Testing");
    }
    // Second line
    sprintf(buffer2, "%d %% ", adcValue);

    lcd_clear();
    lcd_goto_xy(0, 0);
    lcd_write_str(buffer1);
    lcd_goto_xy(1, 0);
    lcd_write_str(buffer2);
    break;
  }
  return state;
}

// Fan SM
unsigned int fanTime = 0;
int FanTick(int state) {
  switch (state) {
  case FAN_INIT:
    state = FanH;
    fanTime = 0;
    break;
  case FanH:
    if (fanTime < FPwmH) {
      state = FanH;
    } else {
      state = FanL;
      fanTime = 0;
    }
    break;
  case FanL:
    if (fanTime < FPwmL) {
      state = FanL;
    } else {
      state = FanH;
      fanTime = 0;
    }
    break;
  default:
    state = FAN_INIT;
    break;
  }

  switch (state) {
  case FanH:
    PORTB |= 0x06;
    break;
  case FanL:
    PORTB &= 0xF9;
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
  lcd_init(); // initializes LCD

  // TODO: Initialize tasks here
  //  e.g. tasks[0].period = TASK1_PERIOD
  //  tasks[0].state = ...
  //  tasks[0].elapsedTime = ...
  //  tasks[0].TickFct = &task1_tick_function;
  tasks[0].period = BUTTON_PERIOD;
  tasks[0].state = IDLE;
  tasks[0].elapsedTime = tasks[0].period;
  tasks[0].TickFct = &ButtonTick;

  tasks[1].period = ADC_PERIOD;
  tasks[1].state = ADC_INIT;
  tasks[1].elapsedTime = tasks[1].period;
  tasks[1].TickFct = &ADC_Tick;

  tasks[2].period = BUZZER_PERIOD;
  tasks[2].state = BUZZER_INIT;
  tasks[2].elapsedTime = tasks[2].period;
  tasks[2].TickFct = &BuzzerTick;

  tasks[3].period = LCD_PERIOD;
  tasks[3].state = LCD_INIT;
  tasks[3].elapsedTime = tasks[3].period;
  tasks[3].TickFct = &LCD_Tick;

  tasks[4].period = FAN_PERIOD;
  tasks[4].state = FAN_INIT;
  tasks[4].elapsedTime = tasks[4].period;
  tasks[4].TickFct = &FanTick;

  TimerSet(GCD_PERIOD);
  TimerOn();
  static char buffer1[16];
  static char buffer2[16];

  while (1) {
    if (forceStop) {
      sprintf(buffer1, "Sys: off");
    } else {
      sprintf(buffer1, "Sys: Testing");
    }
    // Second line
    sprintf(buffer2, "%d %% ", adcValue);

    lcd_clear();
    lcd_goto_xy(0, 0);
    lcd_write_str(buffer1);
    lcd_goto_xy(1, 0);
    lcd_write_str(buffer2);
  }

  return 0;
}
