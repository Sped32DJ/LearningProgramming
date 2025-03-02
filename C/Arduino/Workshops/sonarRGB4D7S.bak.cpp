#include <SevSeg.h>
SevSeg sevseg; // 7-segment display object

// --------------------------
// Pin Definitions
// --------------------------
// Buttons (active LOW using internal pull-ups)
const int onOffButtonPin = 8;      // On/off measurement toggle
const int unitToggleButtonPin = 9; // Toggle between cm and feet

// Sonar sensor (e.g., HC-SR04)
const int triggerPin = 10;
const int echoPin = 11;

// RGB LED (assumed common cathode; use PWM-capable pins)
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

// 7-seg display connections (example configuration)
// Adjust these arrays to match your wiring!
byte numDigits = 4;
byte digitPins[] = {2, 4, 7, 12};
byte segmentPins[] = {A0, A1, A2, A3,
                      A4, A5, 13, 14}; // last pin may be DP (if used)

// --------------------------
// Global Variables
// --------------------------
bool systemOn = false;   // true when measurements are active
bool displayInCm = true; // true to display cm; false to display feet

// Button debouncing (simple state tracking)
bool lastOnOffButtonState = HIGH;
bool lastUnitButtonState = HIGH;

// Sonar measurement variable
float distance = 0.0; // in centimeters

// Timing variables for nonblocking sonar measurements
unsigned long prevMeasureMillis = 0;
const unsigned long measureInterval = 60; // in ms (adjust as needed)

void setup() {
  // Setup serial for debugging
  Serial.begin(9600);

  // Button pins with pull-ups
  pinMode(onOffButtonPin, INPUT_PULLUP);
  pinMode(unitToggleButtonPin, INPUT_PULLUP);

  // Setup sonar sensor pins
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Setup RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Setup SevSeg display
  // For common cathode displays: hardwareConfig = COMMON_CATHODE.
  bool resistorsOnSegments =
      true; // 'true' if your resistors are on the seg pins
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false; // important for nonblocking display updates
  bool leadingZeros = false;     // don't show leading zeros
  bool disableDecPoint =
      true; // disable the decimal point (we'll add one manually in feet mode)

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins,
               resistorsOnSegments, updateWithDelays, leadingZeros,
               disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
  sevseg.refreshDisplay(); // required for multiplexed displays

  // --------------------------
  // Handle Buttons
  // --------------------------
  bool currentOnOffButtonState = digitalRead(onOffButtonPin);
  bool currentUnitButtonState = digitalRead(unitToggleButtonPin);

  // Check on/off button (active LOW)
  if (currentOnOffButtonState == LOW && lastOnOffButtonState == HIGH) {
    systemOn = !systemOn; // toggle measurement state
    // (small debounce delay)
    delay(50);
  }
  lastOnOffButtonState = currentOnOffButtonState;

  // Check unit toggle button (active LOW)
  if (currentUnitButtonState == LOW && lastUnitButtonState == HIGH) {
    displayInCm = !displayInCm; // toggle display units
    delay(50);
  }
  lastUnitButtonState = currentUnitButtonState;

  // --------------------------
  // If system is off: clear display and turn off LED.
  // --------------------------
  if (!systemOn) {
    sevseg.setNumber(0, -1); // display 0 (no decimals)
    setRGB(0, 0, 0);         // turn off RGB LED
    return;
  }

  // --------------------------
  // Sonar Measurement (nonblocking)
  // --------------------------
  unsigned long currentMillis = millis();
  if (currentMillis - prevMeasureMillis >= measureInterval) {
    prevMeasureMillis = currentMillis;
    distance = measureDistance();
  }

  // --------------------------
  // Display the Measurement
  // --------------------------
  float displayVal;
  int decimalPlaces;
  if (displayInCm) {
    // Show centimeters as integer
    displayVal = distance;
    decimalPlaces = -1; // no decimal point
  } else {
    // Convert cm to feet (1 cm = 0.0328084 feet)
    displayVal = distance * 0.0328084;
    decimalPlaces = 1; // show one decimal place
  }
  sevseg.setNumber(displayVal, decimalPlaces);

  // --------------------------
  // Set the RGB LED Color
