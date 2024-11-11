#include "LCD.h"
#include "helper.h"
#include "periph.h"
#include "timerISR.h"
#include <stdio.h>
#include <string.h>

// TODO: declare variables for cross-task communication

/* TODO: match with how many tasks you have */
#define NUM_TASKS 6

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 10; /* TODO: Calulate GCD of tasks */
const unsigned long BUTTON_PERIOD = 500;
const unsigned long ADC_PERIOD = 100;
const unsigned long LCD_PERIOD = 500;
const unsigned long THERMISTER_PERIOD = 300;

const unsigned long BUZZER_PERIOD = 100;

unsigned int Temp = 10;

const unsigned long FAN_PERIOD = 10;
// const unsigned long FAN_PWM_PERIOD = 100;

// PWM Values
// FAN PWM
unsigned short FPwmH = 0;
unsigned short FPwmL = 0;

// Buzzer PWM
unsigned short BPwmH = 0;
unsigned short BPwmL = 10;

bool sbuzz = 0;

task tasks[NUM_TASKS]; // declared task array with 5 tasks

// States
enum Button_States { IDLE, HOLD };
enum ADC_States { ADC_INIT, ADC_READ };
enum Buzzer_States {
  BUZZER_INIT,
  BUZZER_IDLE,
  BUZZER_BLIP,
  BUZZER_OVERHEAT,
  BUZZER_OFF
};
enum LCD_States { LCD_INIT, LCD_WRITE };
enum Thermister_States { THERMISTER_INIT, THERMISTER_READ };
enum Fan_States { FAN_INIT, FanH, FanL };

// Variables

// For button SM
// The system begins initially off
bool forceStop = true;
bool overHeat = false;
bool forward = false;

// for ADC SM
// The range is 0-20 (21 unique vals), 0-9 rev, 10 idle, 11-20 forward
unsigned short adcValue = 0;

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
      sbuzz = true;
      lcd_clear();
    }
    break;
  default:
    state = IDLE;
    break;
  }
  return state;
}

int getTemp() {
  double tempK = log(10000.0 * ((1024.0 / ADC_read(2) - 1)));

  tempK = 1.0 / (0.001129148 +
                 (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK);

  double tempF = (tempK - 273.15) * (9.0 / 5.0) + 32.0;
  return ((tempF + 30) * 3) + 59;
}

int Thermister_Tick(int state) {
  switch (state) {
  case THERMISTER_INIT:
    state = THERMISTER_READ;
    break;
  case THERMISTER_READ:
    state = THERMISTER_READ;
    break;
  default:
    state = THERMISTER_INIT;
    break;
  }
  switch (state) {
  case THERMISTER_READ:
    Temp = getTemp();
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
    adcValue = map(ADC_read(0), 0, 1023, 0, 21);
    if (adcValue >= 0 && adcValue < 9) {
      // Exercise 2 stuff
      if (adcValue < 4) {
        FPwmH = 9;
        FPwmL = 1;
      } else {
        FPwmH = 3;
        FPwmL = 7;
      }
      // FPwmL = adcValue;
      // FPwmH = 10 - adcValue;
      forward = false;
    } else if (adcValue < 12) {
      FPwmH = 0;
      FPwmL = 10;
    } else {
      forward = true;
      if (adcValue < 16) {
        FPwmH = 3;
        FPwmL = 7;
      } else {
        FPwmH = 10;
        FPwmL = 0;
      }
      // FPwmH = adcValue - 10;
      // FPwmL = 10 - (adcValue - 10);
    }

    break;
  }

  return state;
}

// Implement logic for buzzer to go off
unsigned short buzz = 0;
bool lbuzz = 0;
bool isOn = 0;
unsigned int buzzTime = 0;
unsigned int j = 0;
// enum Buzzer_States { BUZZER_INIT, BUZZER_IDLE, BUZZER_BLIP };
int BuzzerTick(int state) {
  ++buzzTime;
  // This causes crashing, I could put a break
  // But this will keep playing until it cools down
  while (overHeat) {
    if (j < 500) {
      PORTB |= 0x01;
    } else if (j < 1000) {
      PORTB &= 0xFE;
    } else if (j < 1500) {
      PORTB |= 0x01;
    } else if (j < 2000) {
      PORTB &= 0xFE;
    } else if (j < 2500) {
      PORTB |= 0x01;
    } else {
      PORTB &= 0xFE;
    }
    _delay_ms(1);
    ++j;
  }
  overHeat = 0;
  j = 0;

  switch (state) {
  case BUZZER_INIT:
    state = BUZZER_IDLE;
    buzzTime = 0;
    sbuzz = 0;
    lbuzz = 0;
    break;
  case BUZZER_IDLE:
    if (sbuzz) {
      sbuzz = 0;
      state = BUZZER_BLIP;
    } else {
      state = BUZZER_IDLE;
    }
    if (Temp > 75 && !overHeat) {
      j = 0;
      overHeat = 1;
      isOn = 0;
      state = BUZZER_OVERHEAT;
    }
    break;
  case BUZZER_BLIP:
    if (sbuzz) {
      state = BUZZER_BLIP;
    } else {
      state = BUZZER_IDLE;
    }
    break;
  default:
    state = BUZZER_INIT;
    break;
  }

  //  if (sbuzz) {
  //    BPwmH = 1;
  //    BPwmL = 9;
  //  } else if (lbuzz) {
  //    BPwmH = 5;
  //    BPwmL = 5;
  //  } else {
  //    BPwmH = 0;
  //    BPwmL = 0;
  //  }

  switch (state) {
  case BUZZER_BLIP:
    PORTB |= 0x01;
    sbuzz = 0;
    state = BUZZER_IDLE;
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
static char buffer1[16];
static char buffer2[16];
// static char prevBuffer2[16];
int LCD_Tick(int state) {
  lcd_clear();

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
    if (forceStop || overHeat) {
      sprintf(buffer1, "Sys: Off");
    } else {
      sprintf(buffer1, "Sys: On");
    }
    // Second line
    // sprintf(buffer2, "%d %% ", FPwmH * 10);
    if (adcValue < 4) {
      sprintf(buffer2, "Rev-Hi       %dF", Temp);
    } else if (adcValue < 9) {
      sprintf(buffer2, "Rev-Low      %dF", Temp);
    } else if (adcValue < 12) {
      sprintf(buffer2, "Neutral      %dF", Temp);
    } else if (adcValue < 16) {
      sprintf(buffer2, "Fwd-Low      %dF", Temp);
    } else {
      sprintf(buffer2, "Fwd-Hi       %dF", Temp);
    }

    // lcd_clear();
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
  ++fanTime;

  switch (state) {
  case FAN_INIT:
    state = FanL;
    fanTime = 0;
    break;
  case FanH:
    if (FPwmH == 0) {
      fanTime = 0;
      state = FanL;
    } else if (fanTime <= FPwmH) {
      state = FanH;
    } else if (fanTime) {
      fanTime = 0;
      state = FanL;
    }
    break;
  case FanL:
    if (FPwmL == 0) {
      fanTime = 0;
      state = FanH;
    } else if (fanTime <= FPwmL) {
      state = FanL;
    } else {
      fanTime = 0;
      state = FanH;
    }
    break;
  default:
    state = FAN_INIT;
    break;
  }

  switch (state) {
  case FAN_INIT:
    break;
  case FanH:
    if (!forceStop && !overHeat && FPwmH > 0) {
      // May need to swap the forward and backwards
      if (forward) {
        // Blow mode
        PORTB |= 0b00000010;
        PORTB &= 0b11111011;
        break;
      } else if (!forward) {
        // Suck mode
        PORTB |= 0b00000100;
        PORTB &= 0b11111101;

        break;
      }
    } else {
      PORTB &= 0xF9; // Both bits off
    }
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
  lcd_clear();

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

  tasks[5].period = THERMISTER_PERIOD;
  tasks[5].state = THERMISTER_INIT;
  tasks[5].elapsedTime = tasks[5].period;
  tasks[5].TickFct = &Thermister_Tick;

  TimerSet(GCD_PERIOD);
  TimerOn();
  // static char buffer1[16];
  // static char buffer2[16];

  while (1) {
  }

  return 0;
}
