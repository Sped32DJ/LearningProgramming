#include "DHT.h"
#include "ST7735.h"
#include "ST7735_Text.h"
#include "helper.h"
#include "irAVR.h"
#include "serialATmega.h"
#include "spiAVR.h"
#include "timerISR.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define NUM_TASKS 9

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
const unsigned long RGB_PERIOD = 100;
const unsigned long DISPLAY_PERIOD = 50;
const unsigned long BUZZER_PERIOD = 1000;
const unsigned long IR_PERIOD = 90;   // Enough to capture the input
const unsigned long RED_PERIOD = 1;   // RedPWM
const unsigned long GREEN_PERIOD = 1; // GreenPWM
const unsigned long BLUE_PERIOD = 1;  // BluePWM
const unsigned long SHIFT_PERIOD = 5; // Still causes Jitters
const unsigned long TIME_PERIOD = 2000;
const unsigned long TEMP_PERIOD = 1000;

task tasks[NUM_TASKS];

enum RGB_States { RGB_INIT, RGB_ON };
enum DISPLAY_States { DISPLAY_INIT, DISPLAY_ON, DISPLAY_OFF };
enum BUZZER_States { BUZZER_INIT, BUZZER_IDLE, BUZZER_GOOD, BUZZER_BAD };
enum IR_States { IR_INIT, IR_IDLE };
enum RED_TICK { RHigh, RLow };
enum GREEN_TICK { GHigh, GLow };
enum BLUE_TICK { BHigh, BLow };
enum SHIFT_States { SHIFT_INIT };
enum TIME_states { CALC };
enum TEMP_states { TEMP_INIT, TEMP_READ };

// NOTE: IR Variables
unsigned char direction = '\0'; // Holds the direction ('u', 'd', 'l', 'r')
long long progressPer = 0;
int rawSeconds = 0;
int timeMin, timeSec;
decode_results results; // Stores decoded results
uint32_t decodeVal = 0;
// Works perfectly fine when this is = 1
// This will help me implement the main menu
unsigned char playGame = 0;

// NOTE: RGB Helpers
// Sets the color of the RGB LED
unsigned char red, green, blue = 0x0;
char currentRed, currentGreen, currentBlue = 0x0;
unsigned char progress = 0;
long long currVal = 0x000;
long long target = 0x000;

// TODO: Not working, give up and do software PWM
int r, RH, RL;
int g, GH, GL;
int b, BH, BL;

// At this poinbt, this is the updateScreen function...
void updateHex() {
  currentRed = (currVal & 0xF00) >> 8;
  currentGreen = (currVal & 0x0F0) >> 4;
  currentBlue = currVal & 0x00F;

  if (currVal == target) {
    progressPer = 100;
    progressPer = (!target) ? 0 : 100;
  } else {
    progressPer = (currVal > target) ? (target * 100) / currVal
                                     : (currVal * 100) / target;
  }
  Screen(0x00); // Fills screen black

  // Hex values
  //  fillBox(9 + 20, 30, 15, 25, 0x00);
  //  fillBox(29 + 20, 30, 15, 25, 0x0);
  //  fillBox(49 + 20, 30, 15, 25, 0x00);

  DrawChar(10, 40, 0xFFFF, 'x');
  DrawChar(10 + 20, 32, 0x001F, currentRed);
  DrawChar(30 + 20, 32, 0x07E0, currentGreen);
  DrawChar(50 + 20, 32, 0xF800, currentBlue);

  // Progress
  //  fillBox(9, 60, 15, 25, 0x00);
  //  fillBox(29, 60, 15, 25, 0x0);
  //  fillBox(49, 60, 15, 25, 0x0);

  if (((progressPer / 100) % 10))
    DrawChar(10, 60, 0xFFFF, (progressPer / 100) % 10);
  if (progressPer > 9)
    DrawChar(30, 60, 0xFFFF, (progressPer / 10) % 10);
  DrawChar(50, 60, 0xFFFF, progressPer % 10);
  DrawChar(70, 65, 0xFFFF, '%');

  // Time
  //  fillBox(9, 90, 15, 25, 0x00);
  //  fillBox(29, 90, 15, 25, 0x0);
  //  fillBox(49, 90, 15, 25, 0x0);

  DrawChar(10, 90, 0x07FF, timeMin);
  DrawChar(26, 90, 0x07FF, ':');
  DrawChar(32, 90, 0x07FF, (timeSec / 10) % 10);
  DrawChar(52, 90, 0x07FF, timeSec % 10);
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

int TEMP_Tick(int state) {
  switch (state) {
  case TEMP_INIT:
    state = TEMP_READ;
    break;
  case TEMP_READ:
    state = TEMP_READ;
    break;
  default:
    state = TEMP_INIT;
    break;
  }
  switch (state) {
  case TEMP_INIT:
    break;
  case TEMP_READ:
    break;
  default:
    break;
  }
  return state;
}

// TODO: Shift register not working yet
void shiftOut(char data) {
  for (int i = 0; i < 8; ++i) {
    // Set the data pin to the correct bit
    PORTD = SetBit(PORTD, 2, GetBit(data, 7 - i)); // DS

    PORTD = SetBit(PORTD, 7, 1); // SH - Clock High
    PORTD = SetBit(PORTD, 7, 0); // SH - Clock low
  }
  PORTD = SetBit(PORTD, 4, 1); // ST - Latch high
  PORTD = SetBit(PORTD, 4, 0); // ST - Latch low
}

int RGB_TICK(int state) {
  switch (state) {
  case RGB_INIT:
    // TODO: Not sure if this works
    target = rand() & 0xFFF;
    // target = 0xF00;
    timeMin = 0;
    timeSec = 0;
    rawSeconds = 0;
    currVal = 0x000;
    red = (target & 0xF00) >> 8;
    green = (target & 0x0F0) >> 4;
    blue = target & 0x00F;

    currVal = 0x000;

    // Setting up PWM periods
    RH = red;
    GH = green;
    BH = blue;

    if (!playGame) {
      RH = 0;
      GH = 0;
      BH = 0;
    }
    RL = RH > 0 ? 16 - RH : 16;
    GL = GH > 0 ? 16 - GH : 16;
    BL = BH > 0 ? 16 - BH : 16;
    if (playGame) {
      state = RGB_ON;
    }
    break;
  case RGB_ON:
    if (direction == 'o') {
      state = RGB_INIT;
      // direction = '\0';
    }
    if (GetBit(PINC, 1)) {
      state = RGB_INIT;
    }
    break;
  default:
    state = RGB_INIT;
    break;
  }
  switch (state) {
  case RGB_INIT:
    break;
  case RGB_ON:
    currentRed = (currVal & 0xF00) >> 8;
    currentGreen = (currVal & 0x0F0) >> 4;
    currentBlue = currVal & 0x00F;

    // Lights up the LED lights when you reach that color!
    if (currentRed == red) {
      progress |= 0x01;
    } else {
      progress &= ~0x01;
    }
    if (currentGreen == green) {
      progress |= 0x02;
    } else {
      progress &= ~0x02;
    }
    if (currentBlue == blue) {
      progress |= 0x04;
    } else {
      progress &= ~0x04;
    }

    break;
  default:
    break;
  }
  return state;
}

// Below are the three RGB tasks (software PWM)
int RED_TICK(int state) {
  switch (state) {
  case RHigh:
    if (r > RH) {
      r = 0;
      state = RLow;
    } else if (r > 13) {
      r = 0;
    }

    break;
  case RLow:
    if (r > RL) {
      r = 0;
      state = RHigh;
    } else if (r > 13) {
      r = 0;
    }
    break;
  default:
    break;
  }
  switch (state) {
  case RHigh:
    ++r;
    PORTD = SetBit(PORTD, 3, 1);
    //  r = (r > 12) ? 0 : r + 1;
    break;
  case RLow:
    ++r;
    PORTD = SetBit(PORTD, 3, 0);
    break;
  default:
    break;
  }
  return state;
}

int GREEN_TICK(int state) {
  switch (state) {
  case GHigh:
    if (g > GH) {
      g = 0;
      state = GLow;
    } else if (g > 13) {
      g = 0;
    }
    break;
  case GLow:
    if (g > GL) {
      g = 0;
      state = GHigh;
    } else if (g > 13) {
      g = 0;
    }
    break;
  }
  switch (state) {
  case GHigh:
    ++g;
    PORTD = SetBit(PORTD, 5, 1);
    break;
  case GLow:
    ++g;
    PORTD = SetBit(PORTD, 5, 0);
    break;
  }
  return state;
}

int BLUE_TICK(int state) {
  switch (state) {
  case BHigh:
    if (b > BH) {
      b = 0;
      state = BLow;
    } else if (b > 13) {
      b = 0;
    }
    break;
  case BLow:
    if (b > BL) {
      b = 0;
      state = BHigh;
    } else if (b > 13) {
      b = 0;
    }
    break;
  }
  switch (state) {
  case BHigh:
    ++b;
    PORTD = SetBit(PORTD, 6, 1);
    break;
  case BLow:
    ++b;
    PORTD = SetBit(PORTD, 6, 0);
    break;
  }

  return state;
}

// White - 0xFFFF
// Red -   0xF800
// Orange - 0xFC00
// Yellow - 0xFFE0
// Green - 0x07E0
// Cyan -  0x07FF
// Blue -  0x001F
// Purple - 0xF81F
// Magenta - 0xF81F
long rainbow[] = {0xF800, 0xFC00, 0xFFE0, 0x07E0,
                  0x07FF, 0x001F, 0xF81F, 0xF81F};
unsigned char colorX = 0;
int DISPLAY_TICK(int state) {
  switch (state) {
  case DISPLAY_INIT:
    rawSeconds = 0;
    timeMin = 0;
    timeSec = 0;
    if (direction == 'o' || playGame) {
      direction = '\0';
      state = DISPLAY_ON;
    }
    break;
  case DISPLAY_ON:
    // NOTE: Make an else that loops into itself?
    if (direction == 'o') {
      direction = '\0';
      // Box(0, 0, 128, 128, 0xFFFF);
      timeMin = 0;
      timeSec = 0;
      state = DISPLAY_OFF;
    }

    // Transition calculates parameters
    if (currVal == target) {
      progressPer = 100;
    } else if (currVal > target) {
      progressPer = (target * 100) / currVal;
    } else {
      progressPer = (currVal * 100) / target;
    }
    timeMin = (rawSeconds / 60);
    timeSec = (rawSeconds % 60);
    if (currVal == target) {
      // Draw the characters with colors cycling through the rainbow vector
      DrawChar(10, 90, rainbow[colorX % 8], timeMin);
      DrawChar(26, 90, rainbow[(colorX + 1) % 8], ':');
      DrawChar(32, 90, rainbow[(colorX + 2) % 8], (timeSec / 10) % 10);
      DrawChar(52, 90, rainbow[(colorX + 3) % 8], timeSec % 10);

      if (IRdecode(&results)) {
        decodeVal = results.value;
        timeMin = 0;
        timeSec = 0;
        rawSeconds = 0;
        playGame = 1;
        currVal = 0x000;
        updateHex();
        IRresume(); // despite calling IRdecode, I still need this (??)
        state = DISPLAY_INIT;
      }

      // Update colorX to cycle
      ++colorX;
      if (colorX > 7) {
        colorX = 0;
      }
      //      if (IRdecode(&results)) {
      //        decodeVal = results.value;
      //        playGame = 0;
      //        updateHex();
      //        Screen(0x00); // Fills screen black
      //        IRresume();   // despite calling IRdecode, I still need this
      //        (??) state = DISPLAY_INIT;
      //      }
    }
    break;
  case DISPLAY_OFF:
    // NOTE: Make an else that loops into itself?
    if (direction == 'o') {
      direction = '\0';
      timeMin = 0;
      timeSec = 0;

      // Screen(0x00); // Fills screen black
      state = DISPLAY_ON;
    }
    break;
  default:
    state = DISPLAY_INIT;
    break;
  }
  // NOTE: Furbish these commands
  switch (state) {
  case DISPLAY_INIT:
    // Screen(0x00);
    if (!playGame) {
      DrawChar(27, 50, rainbow[colorX % 8], 'P');
      DrawChar(47, 50, rainbow[(colorX + 1) % 8], 'L');
      DrawChar(67, 50, rainbow[(colorX + 2) % 8], 'A');
      DrawChar(87, 50, rainbow[(colorX + 3) % 8], 'Y');
      Box(22, 46, 80, 30, 0xFFFF);
    }
    target = rand() & 0xFFF; // Keeps rolling rand()

    if (IRdecode(&results)) {
      decodeVal = results.value;
      playGame = 1;
      updateHex();
      IRresume(); // despite calling IRdecode, I still need this (??)
    }
    //  Box(27, 60, 80, 30, 0xFFFF);

    // Draw the characters with colors cycling through the rainbow vector
    //   DrawChar(10, 90, rainbow[colorX % 8], timeMin);
    //   DrawChar(26, 90, rainbow[(colorX + 1) % 8], ':');
    //   DrawChar(32, 90, rainbow[(colorX + 2) % 8], (timeSec / 10) % 10);
    //   DrawChar(52, 90, rainbow[(colorX + 3) % 8], timeSec % 10);

    // Update colorX to cycle
    ++colorX;
    if (colorX > 7) {
      colorX = 0;
    }

    break;
  case DISPLAY_ON:
    // Turning this on flickers the LED
    // Box(0, 0, 128, 128, 0xFFFF);
    // Pixel(15, 25, 0xFFF0);
    break;
  case DISPLAY_OFF:
    break;
  default:
    break;
  }
  return state;
}

static uint8_t noteIndex = 0;
int timer, freq;

// Define notes for good and fail sounds
const uint16_t goodSound[] = {262, 330, 392, 523}; // C4, E4, G4, C5
const uint16_t failSound[] = {392, 330, 262};      // G4, E4, C4
const uint8_t goodSoundLength = 4;
const uint8_t failSoundLength = 3;

unsigned char triggerGood, triggerBad;

void setBuzzerFreq(uint8_t freq) {
  if (!freq) {
    TCCR1A = 0; // stop buzzer
    return;
  }

  // Configure Timer1 for frequency generation
  DDRB |= (1 << DDB1);                 // Set PB1 (OC1A) as output
  TCCR1A = (1 << COM1A0);              // Toggle OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS10); // CTC mode, no prescaling
  OCR1A = F_CPU / (2 * freq) - 1;      // Set compare match value
}

int BUZZER_TICK(int state) {
  switch (state) {
  case BUZZER_INIT:
    state = BUZZER_IDLE;
    break;
  case BUZZER_IDLE:
    noteIndex = timer = 0;
    if (triggerGood) {
      triggerGood = 0;
      state = BUZZER_GOOD;
    } else if (triggerBad) {
      triggerBad = 0;
      state = BUZZER_BAD;
    }
    break;
  case BUZZER_GOOD:
    if (noteIndex >= goodSoundLength) {
      state = BUZZER_IDLE;
    }
    break;
  case BUZZER_BAD:
    if (noteIndex >= failSoundLength) {
      state = BUZZER_IDLE;
    }
    break;
  default:
    state = BUZZER_INIT;
    break;
  }

  switch (state) {
  case BUZZER_INIT:
    triggerBad = triggerGood = 0;
    break;
  case BUZZER_IDLE:
    TCCR1A = 0; // Turn off Buzzer
    break;
  case BUZZER_GOOD:
    if (!timer) {
      setBuzzerFreq(goodSound[noteIndex]);
      timer = 500;
      ++noteIndex;
    }
    --timer;
    break;
  case BUZZER_BAD:
    if (!timer) {
      setBuzzerFreq(failSound[noteIndex]);
      timer = 500;
      ++noteIndex;
    }
    --timer;
    break;
  default:
    break;
  }
  return state;
}

// TEST: Not sure if this works
int IR_TICK(int state) {
  switch (state) {
  case IR_INIT:
    // IRinit(&DDRC, &PINC, 0); // initializes IR, or it may be DDRC
    state = IR_IDLE;
    break;
  case IR_IDLE:
    if (IRdecode(&results)) {
      decodeVal = results.value;
      //    serial_println(decodeVal);
      //    serial_char(' ');
      //    serial_println(target);
      //    serial_char(' ');
      //    serial_println(currVal);
      //    serial_char(' ');
      //    serial_println(progressPer);
      //    updateTempHum();
      //    serial_println(temperature);
      IRresume(); // despite calling IRdecode, I still need this (??)
    }
    // IRinit(&DDRC, &PINC, 0); // initializes IR, or it may be DDRC
    break;
  default:
    state = IR_INIT;
    break;
  }
  switch (state) {
  case IR_INIT:
    // Drawing the init colors
    break;
  case IR_IDLE:
    // Map the command to a direction
    // This assigns the direction once
    // Once an action is done with the variable,
    // It gets sent to '\0'
    // DEBUGGIN: The PORTD stuff is to debug it works
    if (IRdecode(&results)) {
      decodeVal = results.value;
      //  serial_println(decodeVal);
      //  serial_char(' ');
      //  serial_println(target);
      //  serial_char(' ');
      //  serial_println(currVal);
      //  serial_char(' ');
      //  serial_println(progressPer);
      IRresume(); // despite calling IRdecode, I still need this (??)
    }

    if (decodeVal == 16753245) {
      direction = 'o';
      timeMin = 0;
      timeSec = 0;
      rawSeconds = 0;
      playGame = 1;
      currVal = 0x000;
      updateHex();
      // shiftOut(0x00);
    } else if (decodeVal == 16724175) {
      // ++red (1) 0x001F
      // NOTE: Moving this out of here causes RGB LED flickering
      currVal = (currentRed == 0xF) ? currVal & 0x0FF : currVal;
      currVal = (currentRed < 0xF) ? currVal + 0x100 : currVal;
      // DrawChar(10, 32, 0xFFFF, 'F');
      updateHex();
    } else if (decodeVal == 16716015) {
      // --red (4)
      currVal = (currentRed == 0x0) ? currVal | 0xF00 : currVal;
      currVal = (currentRed > 0x0) ? currVal - 0x100 : currVal;
      // DrawChar(10, 32, 0xFFFF, 'F');
      updateHex();
    } else if (decodeVal == 16718055) {
      // ++green (2)
      currVal = (currentGreen == 0xF) ? currVal & 0xF0F : currVal;
      currVal = (currentGreen < 0xF) ? currVal + 0x010 : currVal;
      // DrawChar(30, 32, 0xFFFF, 'F');
      updateHex();
    } else if (decodeVal == 16726215) {
      // --green (5)
      currVal = (currentGreen == 0x0) ? currVal | 0x0F0 : currVal;
      currVal = (currentGreen > 0x0) ? currVal - 0x010 : currVal;
      // DrawChar(30, 32, 0xFFFF, 'F');
      updateHex();
    } else if (decodeVal == 16743045) {
      // ++blue (3) 0xF800
      currVal = (currentBlue == 0xF) ? currVal & 0xFF0 : currVal;
      currVal = (currentBlue < 0xF) ? currVal + 0x001 : currVal;
      // DrawChar(50, 32, 0xFFFF, 'F');
      updateHex();
    } else if (decodeVal == 16734885) {
      // --blue (6)
      currVal = (currentBlue == 0x0) ? currVal | 0x00F : currVal;
      currVal = (currentBlue > 0x0) ? currVal - 0x001 : currVal;
      // DrawChar(50, 32, 0xFFFF, 'F');
      updateHex();
    } else if (decodeVal == 16738455) { // 0 to update display
      updateHex();
    } else {
      direction = '\0';
      // shiftOut(0x00);
    }
    decodeVal = 0;
    break;
  default:
    break;
  }
  return state;
}

// NOTE: Still flickers, maybe I need a capacitor
// Current period: 1ms
int Shift_Tick(int state) {
  switch (state) {
  case SHIFT_INIT:
    break;
  }
  switch (state) {
  case SHIFT_INIT:
    shiftOut(progress);
    break;
  }
  return state;
}

int ELAPSED_Tick(int state) {
  switch (state) {
  case CALC:
    state = CALC;
    break;
  }
  switch (state) {
  case CALC:
    // Time
    // If I keep this, it is too buggy
    //  fillBox(9, 90, 15, 25, 0x00);
    //  fillBox(29, 90, 15, 25, 0x0);
    //  fillBox(49, 90, 15, 25, 0x0);

    //  DrawChar(10, 90, 0xFFFF, timeMin);
    //  DrawChar(30, 90, 0xFFFF, (timeSec / 10) % 10);
    //  DrawChar(50, 90, 0xFFFF, timeSec % 10);
    if (currVal != target) {
      ++rawSeconds;
      ++rawSeconds;
    }
    break;
  }
  return state;
}

int main(void) {
  // TODO: initialize all your inputs and ouputs
  DDRB = 0xFF;
  PORTB = 0x00;

  // All inputs PORTC
  DDRC = 0x00;
  PORTC = 0xFF;

  DDRD = 0xFF;
  PORTD = 0x00;

  // Debugging Shift Register stuff
  DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) |
          (1 << PD4); // Set PD0, PD1, PD2, PD4 as output
  PORTD &= ~((1 << PD0) | (1 << PD1) | (1 << PD2) |
             (1 << PD4)); // Initialize pins to LOW

  // Sets the timer to normal mode
  // TCCR1B = (1 << CS10); // Start Timer1 with no prescaler; for RGB
  SPI_INIT();
  IRinit(&DDRC, &PINC, 0); // initializes IR, or it may be DDRC
  ST7735_init();           // Initialize display
  Screen(0x00);            // Fills screen black
  serial_init(9600);       // NOTE: Debugging

  //  setupTimer();  // initializes timer
  //  setupPWM();    // initializes PWM
  // srand(getRandomSeed()); // TODO: sync to the crystal or something

  srand(TCNT1); // Seed the random number generator with the current time

  // ADC_init(); // initializes ADC

  // TODO: Initialize tasks here
  //  e.g.
  //  tasks[0].period = ;
  //  tasks[0].state = ;
  //  tasks[0].elapsedTime = ;
  //  tasks[0].TickFct = ;

  tasks[0].period = RGB_PERIOD;
  tasks[0].state = RGB_INIT;
  tasks[0].elapsedTime = tasks[0].period;
  tasks[0].TickFct = &RGB_TICK;

  tasks[1].period = DISPLAY_PERIOD;
  tasks[1].state = DISPLAY_INIT;
  tasks[1].elapsedTime = tasks[1].period;
  tasks[1].TickFct = &DISPLAY_TICK;

  tasks[2].period = BUZZER_PERIOD;
  tasks[2].state = BUZZER_INIT;
  tasks[2].elapsedTime = tasks[2].period;
  tasks[2].TickFct = &BUZZER_TICK;

  tasks[3].period = IR_PERIOD;
  tasks[3].state = IR_INIT;
  tasks[3].elapsedTime = tasks[3].period;
  tasks[3].TickFct = &IR_TICK;

  tasks[4].period = RED_PERIOD;
  tasks[4].state = RHigh;
  tasks[4].elapsedTime = tasks[4].period;
  tasks[4].TickFct = &RED_TICK;

  tasks[5].period = GREEN_PERIOD;
  tasks[5].state = GHigh;
  tasks[5].elapsedTime = tasks[5].period;
  tasks[5].TickFct = &GREEN_TICK;

  tasks[6].period = BLUE_PERIOD;
  tasks[6].state = BHigh;
  tasks[6].elapsedTime = tasks[6].period;
  tasks[6].TickFct = &BLUE_TICK;

  tasks[7].period = SHIFT_PERIOD;
  tasks[7].state = SHIFT_INIT;
  tasks[7].elapsedTime = tasks[7].period;
  tasks[7].TickFct = &Shift_Tick;

  tasks[8].period = TIME_PERIOD;
  tasks[8].state = CALC;
  tasks[8].elapsedTime = tasks[8].period;
  tasks[8].TickFct = &ELAPSED_Tick;

  // MR (unlock) FIX: I think this should be deprecated
  PORTD = SetBit(PORTD, 4, 1);

  // updateHex();

  TimerSet(GCD_PERIOD);
  TimerOn();

  // Box(124, 64, 5, 5, 0xFFFF);

  //
  //   // Draw "Hello!" in white on a black background at (10, 10)
  //  textHandler.drawString(10, 10, "Hello!", 0xFFFF, 0x0000, 1);
  //
  //   // Draw "World!" scaled 2x at (10, 30)
  //   extHandler.drawString(10, 30, "World!", 0xFFFF, 0x0000, 2);

  while (1) {
  }

  return 0;
}
