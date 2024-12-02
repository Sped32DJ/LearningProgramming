// #include "ST7735_Text.h"
#include "ST7735.h"
#include "helper.h"
#include "irAVR.h"
#include "serialATmega.h"
#include "spiAVR.h"
#include "timerISR.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define NUM_TASKS 4

// Task struct for concurrent synchSMs implmentations
typedef struct _task {
  signed char state;         // Task's current state
  unsigned long period;      // Task period
  unsigned long elapsedTime; // Time elapsed since last task tick
  int (*TickFct)(int);       // Task tick function
} task;

// TODO: Define Periods for each task
//  e.g. const unsined long TASK1_PERIOD = <PERIOD>
const unsigned long GCD_PERIOD = 20;
const unsigned long RGB_PERIOD = 500;
const unsigned long DISPLAY_PERIOD = 40;
const unsigned long BUZZER_PERIOD = 40;
const unsigned long IR_PERIOD = 60;

task tasks[NUM_TASKS];

enum RGB_States { RGB_INIT, RGB_ON };
enum DISPLAY_States { DISPLAY_INIT, DISPLAY_ON, DISPLAY_OFF };
enum BUZZER_States { BUZZER_INIT, BUZZER_IDLE, BUZZER_GOOD, BUZZER_BAD };
enum IR_States { IR_INIT, IR_IDLE };

// NOTE: IR Variables
unsigned char direction = '\0'; // Holds the direction ('u', 'd', 'l', 'r')

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

// TODO: Shift register not working yet
void shiftOut(char row) {
  for (int i = 0; i < 8; ++i) {
    // Set the data pin to the correct bit
    PORTD = SetBit(PORTD, 2, GetBit(row, 7 - i)); // DS

    PORTD = SetBit(PORTD, 7, 1); // SH - Clock High
    PORTD = SetBit(PORTD, 7, 0); // SH - Clock low
  }
  PORTD = SetBit(PORTD, 4, 1); // ST - Latch high
  PORTD = SetBit(PORTD, 4, 0); // ST - Latch low
  // PORTD = SetBit(PORTD, 4, 1); // OE (lock)
}

// NOTE: RGB Helpers
// Sets the color of the RGB LED
unsigned char red, green, blue;
uint16_t target = 0x000;
void setColor(unsigned char redVal, unsigned char greenVal,
              unsigned char blueVal) {
  OCR2B = redVal;   // Set RED brightness
  OCR0B = greenVal; // Set GREEN brightness
  OCR0A = blueVal;  // Set BLUE brightness
}

// TODO: Not working, give up and do software PWM
int RGB_TICK(int state) {
  switch (state) {
  case RGB_INIT:
    // TODO: Not sure if this works
    // target = rand() & 0xFFF;
    target = 0x0FF;
    red = (target & 0xF00) >> 8;
    green = (target & 0x0F0) >> 4;
    blue = target & 0x00F;

    state = RGB_ON;
    break;
  case RGB_ON:
    if (direction == 'o') {
      state = RGB_INIT;
      direction = '\0';
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
    // TEST: IF RGB is working
    // Configure PWM for pins 3 (OC2B), 5 (OC0B), and 6 (OC0A)
    // Pin 3 (OC2B) for RED
    DDRD |= (1 << DDD3);                    // Set PD3 as output
    TCCR2A |= (1 << COM2B1) | (1 << WGM20); // Fast PWM, non-inverting mode
    TCCR2B |= (1 << CS21);                  // Prescaler 8
    OCR2B = red << 4;

    // Pin 5 (OC0B) for GREEN
    DDRD |= (1 << DDD5);                    // Set PD5 as output
    TCCR0A |= (1 << COM0B1) | (1 << WGM00); // Fast PWM, non-inverting mode
    TCCR0B |= (1 << CS01);                  // Prescaler 8
    OCR0B = green << 4;

    // Pin 6 (OC0A) for BLUE
    DDRD |= (1 << DDD6);                    // Set PD6 as output
    TCCR0A |= (1 << COM0A1) | (1 << WGM00); // Fast PWM, non-inverting mode
    OCR0A = blue << 4;

    // Sets the brightness of each prime color
    // setColor(red, green, blue);
    break;
  default:
    break;
  }
  return state;
}

int DISPLAY_TICK(int state) {
  switch (state) {
  case DISPLAY_INIT:
    state = DISPLAY_ON;
    break;
  case DISPLAY_ON:
    // NOTE: Make an else that loops into itself?
    if (direction == 'o') {
      direction = '\0';
      HardwareReset();
      state = DISPLAY_OFF;
    }
    break;
  case DISPLAY_OFF:
    // NOTE: Make an else that loops into itself?
    if (direction == 'o') {
      direction = '\0';
      HardwareReset();
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
    break;
  case DISPLAY_ON:
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
decode_results results; // Stores decoded results
uint32_t decodeVal = 0;
int IR_TICK(int state) {
  switch (state) {
  case IR_INIT:
    IRinit(&DDRC, &PINC, 0); // initializes IR, or it may be DDRC
    state = IR_IDLE;
    break;
  case IR_IDLE:
    if (IRdecode(&results)) {
      decodeVal = results.value;
      serial_println(results.value);
    }
    IRresume();              // despite calling IRdecode, I still need this (??)
    IRinit(&DDRC, &PINC, 0); // initializes IR, or it may be DDRC
    break;
  default:
    state = IR_INIT;
    break;
  }
  switch (state) {
  case IR_INIT:
    break;
  case IR_IDLE:
    // Map the command to a direction
    // This assigns the direction once
    // Once an action is done with the variable,
    // It gets sent to '\0'
    // DEBUGGIN: The PORTD stuff is to debug it works
    if (decodeVal == 16736925) {
      direction = 'u';
    } else if (decodeVal == 16754775) {
      direction = 'd';
    } else if (decodeVal == 16720605) {
      direction = 'l';
      shiftOut(0x04);
    } else if (decodeVal == 16761405) {
      direction = 'r';
      shiftOut(0x01);
    } else if (decodeVal == 16712445) {
      direction = 'c';
      shiftOut(0x02);
    } else if (decodeVal == 16753245) {
      direction = 'o';
      shiftOut(0x00);
    } else {
      direction = '\0';
      shiftOut(0x00);
    }
    decodeVal = 0;
    break;
  default:
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
  ST7735_init(); // Initialize display
  Screen(0x0000);
  serial_init(9600);
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
  PORTD = SetBit(PORTD, 4, 1); // MR (unlock)

  TimerSet(GCD_PERIOD);
  TimerOn();

  //  // NOTE: Clear below
  //  // Clear the screen with black
  // Clear_Screen_With_Color(0x0F00);
  //
  //  // Draw "Hello!" in white on a black background at (10, 10)
  //  textHandler.drawString(10, 10, "Hello!", 0xFFFF, 0x0000, 1);
  //
  //  // Draw "World!" scaled 2x at (10, 30)
  //  extHandler.drawString(10, 30, "World!", 0xFFFF, 0x0000, 2);

  while (1) {
  }

  return 0;
}
