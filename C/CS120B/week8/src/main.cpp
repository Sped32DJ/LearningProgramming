#include "helper.h"
#include "periph.h"
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
const unsigned long GCD_PERIOD = 50; // TODO:Set the GCD Period
const unsigned long RGB_PERIOD = 500;
const unsigned long DISPLAY_PERIOD = 50;
const unsigned long BUZZER_PERIOD = 50;
const unsigned long IR_PERIOD = 50;

task tasks[NUM_TASKS];

enum RGB_States { RGB_INIT, RGB_ON };
enum DISPLAY_States { DISPLAY_INIT, DISPLAY_ON, DISPLAY_OFF };
enum BUZZER_States { BUZZER_INIT, BUZZER_IDLE };
enum IR_States { IR_INIT, IR_IDLE };

// NOTE: IR Helpers
volatile uint8_t ir_flag = 0;   // Flag indicating an IR signal was received
volatile uint32_t ir_data = 0;  // Variable to store the decoded IR data
unsigned char direction = '\0'; // Holds the direction ('u', 'd', 'l', 'r')

// TEST: Everything until decodeNEC
void setupTimer1() {
  // Configure Timer1 in normal mode
  TCCR1A = 0;
  TCCR1B = (1 << CS11); // Prescaler 8 for microsecond timing

  // Enable input capture interrupt
  TIMSK1 |= (1 << ICIE1);
}

// TEST: This may get the boot
ISR(TIMER1_CAPT_vect) {
  static uint8_t bit_count = 0;
  static uint32_t data = 0;

  uint16_t pulse_width = ICR1; // Capture pulse width
  TCNT1 = 0;                   // Reset timer for next measurement

  // Decode the pulse based on NEC timing
  if (pulse_width > 10000) {
    // Leader pulse detected, reset for new frame
    bit_count = 0;
    data = 0;
  } else if (pulse_width > 2000) {
    // Invalid timing, ignore
  } else if (pulse_width > 1125) {
    // Logical 1 detected
    data = (data << 1) | 1;
    bit_count++;
  } else if (pulse_width > 562) {
    // Logical 0 detected
    data = (data << 1);
    bit_count++;
  }

  // Check if 32 bits received
  if (bit_count == 32) {
    ir_raw_data = data;
    ir_flag = 1; // Signal that a frame is ready
  }
}

// TEST: idk about this
void setupIR() {
  // Set PD2 (INT0) as input for IR receiver
  DDRD &= ~(1 << PD2);

  // Configure Timer1 for pulse measurement
  setupTimer1();

  // Enable global interrupts
  sei();
}

void decodeNEC(uint32_t raw_data) {
  uint8_t address = (raw_data >> 24) & 0xFF;
  uint8_t inverted_address = (raw_data >> 16) & 0xFF;
  uint8_t command = (raw_data >> 8) & 0xFF;
  uint8_t inverted_command = raw_data & 0xFF;

  // Validate the inverted bits
  if ((address ^ inverted_address) == 0xFF &&
      (command ^ inverted_command) == 0xFF) {
    // Map the command to a direction
    switch (command) {
    case 0x46: // Up button
      direction = 'u';
      break;
    case 0x15: // Down button
      direction = 'd';
      break;
    case 0x44: // Left button
      direction = 'l';
      break;
    case 0x43: // Right button
      direction = 'r';
      break;
    default:
      direction = '\0'; // Invalid or unhandled command
      break;
    }
  }
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

// NOTE: RGB Helpers
// Sets the color of the RGB LED
void setColor(unsigned char redVal, unsigned char greenVal,
              unsigned char blueVal) {
  OCR2B = redVal;   // Set RED brightness
  OCR0B = greenVal; // Set GREEN brightness
  OCR0A = blueVal;  // Set BLUE brightness
}

// uint16_t getRandomSeed() {
//   uint16_t noise = readAnalogNoise();
//   uint16_t time = TCNT1;
//   return noise ^ time; // XOR for combined randomness
// }

unsigned char red, green, blue;
int RGB_TICK(int state) {
  switch (state) {
  case RGB_INIT:
    // TODO: Properly reset colors
    red = rand();
    green = rand();
    blue = rand();

    state = RGB_ON;
    break;
  case RGB_ON:
    state = RGB_ON;
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

    // Pin 5 (OC0B) for GREEN
    DDRD |= (1 << DDD5);                    // Set PD5 as output
    TCCR0A |= (1 << COM0B1) | (1 << WGM00); // Fast PWM, non-inverting mode
    TCCR0B |= (1 << CS01);                  // Prescaler 8

    // Pin 6 (OC0A) for BLUE
    DDRD |= (1 << DDD6);                    // Set PD6 as output
    TCCR0A |= (1 << COM0A1) | (1 << WGM00); // Fast PWM, non-inverting mode

    // Sets the brightness of each prime color
    setColor(red, green, blue);
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
    state = DISPLAY_OFF;
    break;
  case DISPLAY_OFF:
    state = DISPLAY_ON;
    break;
  default:
    state = DISPLAY_INIT;
    break;
  }
  switch (state) {
  case DISPLAY_INIT:
    break;
  case DISPLAY_ON:
    PORTB = 0xFF;
    break;
  case DISPLAY_OFF:
    PORTB = 0x00;
    break;
  default:
    break;
  }
  return state;
}

int BUZZER_TICK(int state) {
  switch (state) {
  case BUZZER_INIT:
    state = BUZZER_IDLE;
    break;
  case BUZZER_IDLE:
    state = BUZZER_IDLE;
    break;
  default:
    state = BUZZER_INIT;
    break;
  }
  switch (state) {
  case BUZZER_INIT:
    break;
  case BUZZER_IDLE:
    break;
  default:
    break;
  }
  return state;
}

int IR_TICK(int state) {
  switch (state) {
  case IR_INIT:
    state = IR_IDLE;
    break;
  case IR_IDLE:
    state = IR_IDLE;
    if (ir_flag) {
      decodeNEC(ir_data);
      ir_flag = 0;
    }
    break;
  default:
    state = IR_INIT;
    break;
  }
  switch (state) {
  case IR_INIT:
    break;
  case IR_IDLE:
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

  // Sets the timer to normal mode
  TCCR1B = (1 << CS10); // Start Timer1 with no prescaler; for RGB
  setupIR();            // initializes IR
  setupTimer();         // initializes timer
  setupPWM();           // initializes PWM
  // srand(getRandomSeed()); // TODO: sync to the crystal or something

  srand(TCNT1); // Seed the random number generator with the current time

  ADC_init(); // initializes ADC

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

  TimerSet(GCD_PERIOD);
  TimerOn();

  while (1) {
  }

  return 0;
}
//
