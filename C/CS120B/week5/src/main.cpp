#include "helper.h"
#include "periph.h"
#include "timerISR.h"

// TODO: Change this depending on which exercise you are doing.
// Exercise 1: 3 tasks
// Exercise 2: 5 tasks
// Exercise 3: 7 tasks
#define NUM_TASKS 7

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

const unsigned long RED_PERIOD = 1;
const unsigned long RED_PWN = 10;

const unsigned long GREEN_PERIOD = 1;
const unsigned long GREEN_PWN = 10;

// remove const for ex3
unsigned int threhold_close = 8;
unsigned int threhold_far = 12;

// Red iterator
int j = 0;
unsigned char RedH = 0;
unsigned char RedL = 0;

// Green iterator
int k = 0;
unsigned char GreenH = 0;
unsigned char GreenL = 0;

// Exercise 3
const unsigned long RIGHT_PERIOD = 200;
const unsigned long BLUE_PERIOD = 250;

unsigned char BlueH = 0;
unsigned char BlueL = 0;
unsigned int rightWaitThree = 0;

task tasks[NUM_TASKS]; // declared task array with NUM_TASKS amount of tasks

enum SNAR_States { SonarInit, SONAR_S1 };
volatile double distance = 0;
unsigned char in_distance = 69;
unsigned char cm_distance = 169;

enum DISP_States { displayInit, disp_S1, disp_S2, disp_S3, disp_S4 };
bool isInches = false; // default metric (yucky); true = imperial

enum Left_States { leftInit, Left_S1, Left_S2 };
unsigned char LeftButton() { return !GetBit(PINC, 1); }

enum Red_States { RedInit, RPwmH, RPwmL };
enum Green_States { GreenInit, GPwmH, GPwmL };

enum Right_States { rightInit, Right_S1, Right_S2 };
unsigned char RightButton() { return !GetBit(PINC, 0); }

enum Blue_States { BlueInit, BPwmH, BPwmL };

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
  default:
    state = SonarInit;
    break;
  }

  // State Actions
  switch (state) {
  case SONAR_S1:
    // sonar_read() outputs cm by default + .50 rounding
    distance = sonar_read();
    in_distance = int(distance / 2.54);
    cm_distance = int(distance);

    // NOTE: Hopefully this works soon
    // serial_println(in_distance);
    if (cm_distance < threhold_close && BlueH == 0) {

      RedH = 10;
      RedL = 0;

      GreenH = 0;
      GreenL = 10;
      PORTC &= 0xEF; // Turn off green LED
    } else if ((cm_distance >= threhold_close) &&
               (cm_distance <= threhold_far) && BlueH == 0) {
      PORTC &= 0xF7; // Turn off Red LED
      PORTC &= 0xEF; // Turn off green LED

      RedH = 9;
      RedL = 1;

      GreenH = 3;
      GreenL = 7;
    } else if (cm_distance > threhold_far && BlueH == 0) {
      RedH = 0;
      RedL = 10;

      GreenH = 10;
      GreenL = 0;
    }

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
  default:
    state = displayInit;
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
  default:
    state = leftInit;
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

int red_TckFct(int state) {
  // Transitions
  switch (state) {
  case RedInit:
    j = 0;
    state = RPwmH;
    break;
  case RPwmH:
    if (j < RedH) {
      state = RPwmH;
    } else {
      state = RPwmL;
      j = 0;
    }
    break;
  case RPwmL:
    if (j < RedL) {
      state = RPwmL;
    } else {
      state = RPwmH;
      j = 0;
    }
    break;
  default:
    state = RedInit;
    break;
  }

  // State Actions
  switch (state) {
  case RedInit:
    PORTC &= 0xF7; // Turn off Red LED
    ++j;
    break;
  case RPwmH:
    if (cm_distance < threhold_close && rightWaitThree > 15) {
      PORTC |= 0x08; // Turn on Red LED
    } else {
      PORTC &= 0xF7; // Turn off Red LED
    }
    PORTC |= 0x08; // Turn on Red LED
    ++j;
    break;
  case RPwmL:
    PORTC &= 0xF7; // Turn off Red LED
    ++j;
    break;
  default:
    break;
  }
  return state;
}

int green_TckFct(int state) {
  // Transitions
  switch (state) {
  case GreenInit:
    state = GPwmH;
    k = 0;
    break;
  case GPwmH:
    if (k < GreenH) {
      state = GPwmH;
    } else {
      state = GPwmL;
      k = 0;
    }
    break;
  case GPwmL:
    if (k < GreenL) {
      state = GPwmL;
    } else {
      state = GPwmH;
      k = 0;
    }
    break;
  default:
    state = GreenInit;
    break;
  }

  // State Actions
  switch (state) {
  case GreenInit:
    PORTC &= 0xEF; // Turn off green LED
    break;
  case GPwmH:
    // Bandaid ovver the problem
    if (cm_distance < threhold_close && rightWaitThree > 15) {
      PORTC &= 0xEF; // Turn off green LED
    } else {
      PORTC |= 0x10; // Turn on Green LED
    }
    ++k;
    break;
  case GPwmL:
    // Turn off green LED
    PORTC &= 0xEF;
    ++k;
    break;
  }

  return state;
}

int right_TckFct(int state) {
  // Transitions
  switch (state) {
  case rightInit:
    state = Right_S1;
    break;
  case Right_S1:
    if (!RightButton()) {
      state = Right_S2;
      rightWaitThree = 0;
    }
    break;
  case Right_S2:
    if (RightButton()) {
      threhold_close = cm_distance * 4 / 5;
      threhold_far = cm_distance * 6 / 5;
      state = Right_S1;
    }
    break;
  default:
    state = rightInit;
    break;
  }

  // State Actions
  switch (state) {
  case Right_S1:
    if (rightWaitThree < 15) {
      BlueH = 10;
      BlueL = 0;
    } else {
      rightWaitThree = 16;
      BlueH = 0;
      BlueL = 10;
    }
    ++rightWaitThree;
    break;
  }
  return state;
}

unsigned int b = 0;
int blue_TckFct(int state) {
  switch (state) {
  case BlueInit:
    b = 0;
    state = BPwmH;
    break;
  case BPwmH:
    if (b < BlueH) {
      state = BPwmH;
    } else {
      state = BPwmL;
      b = 0;
    }
    break;

  case BPwmL:
    if (b < BlueL) {
      state = BPwmL;
    } else {
      state = BPwmH;
      b = 0;
    }
    break;
  default:
    state = BlueInit;
    break;
  }

  switch (state) {
  case BlueInit:
    break;
  case BPwmH:
    ++b;
    if (rightWaitThree < 15) {
      if (rightWaitThree % 2 == 0) {
        PORTC |= 0x20;
      } else {
        PORTC &= 0xC7;
      }
    }

    break;
  case BPwmL:
    ++b;
    PORTC &= 0xDF;
  }
  return state;
}

void TimerISR() {
  for (unsigned int i = 0; i < NUM_TASKS; i++) {
    // Iterate through each task in the task array
    if (tasks[i].elapsedTime == tasks[i].period) {
      // Check if the task is ready to tick
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      // Tick and set the next state for this task
      tasks[i].elapsedTime = 0; // Reset the elapsed time for the next tick
    }
    tasks[i].elapsedTime += GCD_PERIOD;
    // Increment the elapsed time by GCD_PERIOD
  }
}

int main(void) {
  DDRD = 0xFF;
  PORTD = 0x00;

  DDRB = 0xFE;
  PORTB = 0x01;

  DDRC = 0xFC;
  PORTC = 0x03;

  ADC_init();   // initializes ADC
  sonar_init(); // initializes sonar
                // serial_init(9600); // Helps debugging

  tasks[0].state = SonarInit;
  tasks[0].period = SNAR_PERIOD;
  tasks[0].elapsedTime = tasks[0].period;
  tasks[0].TickFct = &sonar_TickFct;

  tasks[1].state = displayInit;
  tasks[1].period = DISP_PERIOD;
  tasks[1].elapsedTime = tasks[1].period;
  tasks[1].TickFct = &display_TickFct;

  tasks[2].state = leftInit;
  tasks[2].period = LEFT_PERIOD;
  tasks[2].elapsedTime = tasks[2].period;
  tasks[2].TickFct = &left_TckFct;

  tasks[3].state = RedInit;
  tasks[3].period = RED_PERIOD;
  tasks[3].elapsedTime = tasks[3].period;
  tasks[3].TickFct = &red_TckFct;

  tasks[4].state = GreenInit;
  tasks[4].period = GREEN_PERIOD;
  tasks[4].elapsedTime = tasks[4].period;
  tasks[4].TickFct = &green_TckFct;

  tasks[5].state = rightInit;
  tasks[5].period = RIGHT_PERIOD;
  tasks[5].elapsedTime = tasks[5].period;
  tasks[5].TickFct = &right_TckFct;

  tasks[6].state = BlueInit;
  tasks[6].period = BLUE_PERIOD;
  tasks[6].elapsedTime = tasks[6].period;
  tasks[6].TickFct = &blue_TckFct;

  TimerSet(GCD_PERIOD);
  TimerOn();

  // loop stays empty
  while (1) {
  }

  return 0;
}
