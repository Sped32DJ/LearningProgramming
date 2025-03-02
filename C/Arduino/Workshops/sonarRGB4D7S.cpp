#include <SevSeg.h>
SevSeg sevseg; // 7-segment display object

// --------------------------
// Pin Definitions
// --------------------------
// Buttons (active LOW using internal pull-ups)
const int onOffButtonPin = 8;      // On/Off measurement toggle
const int unitToggleButtonPin = 9; // Toggle between cm and feet

// Sonar sensor (e.g., HC-SR04)
const int triggerPin = 10;
const int echoPin = 11;

// RGB LED (assumed common cathode; use PWM-capable pins)
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

// 7-Segment display configuration (example wiring)
// Adjust these arrays to match your wiring!
const byte numDigits = 4;
byte digitPins[] = {2, 4, 7, 12};
byte segmentPins[] = {A0, A1, A2, A3, A4, A5, 13, 14}; // last pin may be DP

// --------------------------
// Global Variables
// --------------------------
volatile bool systemOn = false;   // Set by on/off button
volatile bool displayInCm = true; // true: display cm, false: display feet
volatile float distance = 0.0;    // Measured distance (in cm)

// --------------------------
// On/Off Button State Machine
// --------------------------
enum OnOffState { OB_WAIT, OB_PRESSED, OB_RELEASED };
OnOffState onOffState = OB_WAIT;
unsigned long onOffDebounceTime = 0;
const unsigned long debounceDelay = 50; // milliseconds

void Tick_OnOffButtonSM() {
  int reading = digitalRead(onOffButtonPin);
  unsigned long currentMillis = millis();

  switch (onOffState) {
  case OB_WAIT:
    if (reading == LOW) {
      onOffState = OB_PRESSED;
      onOffDebounceTime = currentMillis;
    }
    break;

  case OB_PRESSED:
    // Wait for debounce period
    if (currentMillis - onOffDebounceTime >= debounceDelay) {
      // Confirm button is still pressed
      if (digitalRead(onOffButtonPin) == LOW) {
        systemOn = !systemOn; // Toggle system on/off
        onOffState = OB_RELEASED;
      } else {
        onOffState = OB_WAIT;
      }
    }
    break;

  case OB_RELEASED:
    if (reading == HIGH) {
      onOffState = OB_WAIT;
    }
    break;
  }
}

// --------------------------
// Unit Toggle Button State Machine
// --------------------------
enum UnitState { UB_WAIT, UB_PRESSED, UB_RELEASED };
UnitState unitState = UB_WAIT;
unsigned long unitDebounceTime = 0;

void Tick_UnitButtonSM() {
  int reading = digitalRead(unitToggleButtonPin);
  unsigned long currentMillis = millis();

  switch (unitState) {
  case UB_WAIT:
    if (reading == LOW) {
      unitState = UB_PRESSED;
      unitDebounceTime = currentMillis;
    }
    break;

  case UB_PRESSED:
    if (currentMillis - unitDebounceTime >= debounceDelay) {
      if (digitalRead(unitToggleButtonPin) == LOW) {
        displayInCm = !displayInCm; // Toggle units
        unitState = UB_RELEASED;
      } else {
        unitState = UB_WAIT;
      }
    }
    break;

  case UB_RELEASED:
    if (reading == HIGH) {
      unitState = UB_WAIT;
    }
    break;
  }
}

// --------------------------
// Sonar Sensor State Machine
// --------------------------
enum SonarState { SONAR_IDLE, SONAR_TRIGGER, SONAR_WAIT_ECHO, SONAR_PROCESS };
SonarState sonarState = SONAR_IDLE;
unsigned long sonarTimer = 0;
unsigned long sonarStartTime = 0;
unsigned long sonarEndTime = 0;
const unsigned long sonarInterval = 60; // ms between measurements

void Tick_SonarSM() {
  unsigned long currentMillis = millis();

  // Run the sonar SM only if the system is on
  if (!systemOn) {
    sonarState = SONAR_IDLE;
    return;
  }

  switch (sonarState) {
  case SONAR_IDLE:
    // Start a new measurement at defined intervals
    if (currentMillis - sonarTimer >= sonarInterval) {
      sonarTimer = currentMillis;
      sonarState = SONAR_TRIGGER;
    }
    break;

  case SONAR_TRIGGER:
    // Trigger the sensor (using minimal blocking delays for microsecond
    // precision)
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    sonarState = SONAR_WAIT_ECHO;
    break;

  case SONAR_WAIT_ECHO:
    // Wait until echo pin goes HIGH (start of echo)
    if (digitalRead(echoPin) == HIGH) {
      sonarStartTime = micros();
      sonarState = SONAR_PROCESS;
    }
    break;

  case SONAR_PROCESS:
    // Wait until echo pin goes LOW (end of echo)
    if (digitalRead(echoPin) == LOW) {
      sonarEndTime = micros();
      long duration = sonarEndTime - sonarStartTime;
      // Compute distance in cm. (Divide by 58 approximates the conversion.)
      distance = duration / 58.0;
      sonarState = SONAR_IDLE;
    }
    break;
  }
}

// --------------------------
// 7-Segment Display State Machine
// --------------------------
enum DisplayState { DISP_UPDATE };
DisplayState displayState = DISP_UPDATE;

void Tick_DisplaySM() {
  // If system is off, show 0
  if (!systemOn) {
    sevseg.setNumber(0, -1);
    return;
  }

  // Determine value to display and the number of decimals
  float displayVal;
  int decimals;
  if (displayInCm) {
    displayVal = distance;
    decimals = -1; // no decimal point
  } else {
    // Convert cm to feet (1 cm = 0.0328084 feet)
    displayVal = distance * 0.0328084;
    decimals = 1; // one decimal place
  }
  sevseg.setNumber(displayVal, decimals);
}

// --------------------------
// RGB LED State Machine
// --------------------------
enum RGBState { RGB_UPDATE };
RGBState rgbState = RGB_UPDATE;

void Tick_RGBSM() {
  // If system is off, turn off LED
  if (!systemOn) {
    setRGB(0, 0, 0);
    return;
  }

  // Use distance in cm for thresholds:
  // 0-10 cm: Too close → Red
  // 11-15 cm: At range → Green
  // >15 cm: Too far → Blue
  if (distance <= 10) {
    setRGB(255, 0, 0);
  } else if (distance <= 15) {
    setRGB(0, 255, 0);
  } else {
    setRGB(0, 0, 255);
  }
}

// --------------------------
// Helper Function: setRGB()
// Sets the RGB LED color (assumes common cathode)
void setRGB(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
}

// --------------------------
// Setup Function
// --------------------------
void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);

  // Button pins with internal pull-ups
  pinMode(onOffButtonPin, INPUT_PULLUP);
  pinMode(unitToggleButtonPin, INPUT_PULLUP);

  // Setup sonar sensor pins
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Setup RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Setup 7-seg display using SevSeg library
  bool resistorsOnSegments = true;      // if your resistors are on the seg pins
  byte hardwareConfig = COMMON_CATHODE; // adjust if you use common anode
  bool updateWithDelays = false;        // nonblocking display refresh
  bool leadingZeros = false;
  bool disableDecPoint = true; // we'll manage decimal point manually
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins,
               resistorsOnSegments, updateWithDelays, leadingZeros,
               disableDecPoint);
  sevseg.setBrightness(90);
}

// --------------------------
// Main Loop: Call all Tick functions
// --------------------------
void loop() {
  // Refresh the 7-seg display (required for multiplexed displays)
  sevseg.refreshDisplay();

  // Call each state machine's Tick function
  Tick_OnOffButtonSM();
  Tick_UnitButtonSM();
  Tick_SonarSM();
  Tick_DisplaySM();
  Tick_RGBSM();
}
