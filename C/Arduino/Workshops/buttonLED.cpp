// Very simple circuit with a button and an LED.
// The button toggles the LED

const int buttonPin = A0; // PC0
const int ledPin = 2;     // PD2

enum ButtonState { IDLE, PRESSED, RELEASED };
ButtonState buttonState = IDLE;

bool ledState = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  static bool lastButtonState = HIGH;
  bool buttonStateNow = digitalRead(buttonPin);

  switch (buttonState) {
  case IDLE:
    if (buttonStateNow == LOW && lastButtonState == HIGH) {
      buttonState = PRESSED;
    }
    break;

  case PRESSED:
    if (buttonStateNow == LOW) {
      buttonState = RELEASED;
      ledState = !ledState; // Toggle LED
      digitalWrite(ledPin, ledState);
    }
    break;

  case RELEASED:
    if (buttonStateNow == HIGH) {
      buttonState = IDLE; // Ready for next press
    }
    break;
  }

  lastButtonState = buttonStateNow;
}
