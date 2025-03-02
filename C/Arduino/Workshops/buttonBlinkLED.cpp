// Very simple circuit with a button (on A0, PC0) and an LED (on digital pin 2,
// PD2). Single click toggles the LED (when not in blink mode). A double click
// toggles blink mode, where the LED blinks automatically.

const int buttonPin = A0; // PC0
const int ledPin = 2;     // PD2

// --- Button State Machine Definitions ---
enum ButtonSMState {
  BUTTON_IDLE,
  BUTTON_DEBOUNCE_PRESS,
  BUTTON_WAIT_FOR_RELEASE,
  BUTTON_WAIT_FOR_SECOND,
  BUTTON_DEBOUNCE_SECOND_PRESS,
  BUTTON_WAIT_FOR_SECOND_RELEASE
};
ButtonSMState btnState = BUTTON_IDLE;

unsigned long btnTimer = 0;
const unsigned long debounceDelay = 50;      // milliseconds debounce
const unsigned long doubleClickWindow = 400; // ms window for a double click

// Global flags used by the LED state machine
volatile bool ledToggleEvent = false;  // Set on a single click event
volatile bool blinkModeActive = false; // Toggled by a double click

// --- LED State Machine Definitions ---
unsigned long lastLedTime = 0;
const unsigned long blinkInterval = 250; // ms for automatic blinking
bool ledOutputState = false;             // current LED state

// Tick function for the button state machine
void Tick_ButtonSM() {
  int reading = digitalRead(buttonPin);
  unsigned long now = millis();

  switch (btnState) {
  case BUTTON_IDLE:
    if (reading == LOW) { // button pressed
      btnState = BUTTON_DEBOUNCE_PRESS;
      btnTimer = now;
    }
    break;

  case BUTTON_DEBOUNCE_PRESS:
    if (now - btnTimer >= debounceDelay) {
      if (reading == LOW) {
        btnState = BUTTON_WAIT_FOR_RELEASE;
      } else {
        btnState = BUTTON_IDLE;
      }
    }
    break;

  case BUTTON_WAIT_FOR_RELEASE:
    if (reading == HIGH) { // button released after first press
      btnState = BUTTON_WAIT_FOR_SECOND;
      btnTimer = now; // start timing for a potential second press
    }
    break;

  case BUTTON_WAIT_FOR_SECOND:
    if (reading == LOW) { // second press detected
      btnState = BUTTON_DEBOUNCE_SECOND_PRESS;
      btnTimer = now;
    } else if (now - btnTimer >= doubleClickWindow) {
      // No second press: it's a single click event.
      ledToggleEvent = true;
      btnState = BUTTON_IDLE;
    }
    break;

  case BUTTON_DEBOUNCE_SECOND_PRESS:
    if (now - btnTimer >= debounceDelay) {
      if (reading == LOW) {
        btnState = BUTTON_WAIT_FOR_SECOND_RELEASE;
      } else {
        // if button released too soon, consider it a single click.
        ledToggleEvent = true;
        btnState = BUTTON_IDLE;
      }
    }
    break;

  case BUTTON_WAIT_FOR_SECOND_RELEASE:
    if (reading == HIGH) {
      // Double click successfully detected!
      blinkModeActive = !blinkModeActive; // Toggle blink mode
      btnState = BUTTON_IDLE;
    }
    break;
  }
}

// Tick function for the LED state machine
void Tick_LED_SM() {
  unsigned long now = millis();

  if (blinkModeActive) {
    // In blink mode, the LED toggles automatically at a fixed interval.
    if (now - lastLedTime >= blinkInterval) {
      lastLedTime = now;
      ledOutputState = !ledOutputState;
      digitalWrite(ledPin, ledOutputState);
    }
  } else {
    // In normal mode, we only act when a single click event is flagged.
    if (ledToggleEvent) {
      ledToggleEvent = false;
      ledOutputState = !ledOutputState;
      digitalWrite(ledPin, ledOutputState);
    }
  }
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Call tick functions for each independent state machine.
  Tick_ButtonSM();
  Tick_LED_SM();
}
