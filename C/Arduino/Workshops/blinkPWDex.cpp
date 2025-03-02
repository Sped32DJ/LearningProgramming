const int buttonPin = A0; // PC0
const int ledPin = 2;     // PD2 (PWM)

enum State { IDLE, BLINK, FADE_UP, FADE_DOWN };
State ledState = IDLE;

bool lastButtonState = HIGH;
bool buttonPressed = false;
unsigned long prevMillis = 0;
int blinkCount = 0;
int fadeValue = 0;
bool fadeUp = true;
int fadeCycle = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Button_Tick();
  LED_Tick();
}

void Button_Tick() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    buttonPressed = !buttonPressed; // Toggle sequence on/off
    ledState = buttonPressed ? BLINK : IDLE;
    blinkCount = 0;
    fadeCycle = 0;
  }

  lastButtonState = buttonState;
}

void LED_Tick() {
  unsigned long currentMillis = millis();

  switch (ledState) {
  case IDLE:
    digitalWrite(ledPin, LOW);
    break;

  case BLINK:
    if (currentMillis - prevMillis >= 250) {
      prevMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin));
      blinkCount++;

      if (blinkCount >= 8) { // 4 blinks (ON/OFF cycles)
        blinkCount = 0;
        ledState = FADE_UP;
      }
    }
    break;

  case FADE_UP:
    if (currentMillis - prevMillis >= 10) {
      prevMillis = currentMillis;
      analogWrite(ledPin, fadeValue);
      fadeValue += 5;

      if (fadeValue >= 255) {
        fadeValue = 255;
        ledState = FADE_DOWN;
      }
    }
    break;

  case FADE_DOWN:
    if (currentMillis - prevMillis >= 10) {
      prevMillis = currentMillis;
      analogWrite(ledPin, fadeValue);
      fadeValue -= 5;

      if (fadeValue <= 0) {
        fadeValue = 0;
        fadeCycle++;

        if (fadeCycle < 2) {
          ledState = FADE_UP; // Repeat fade twice
        } else {
          fadeCycle = 0;
          ledState = BLINK; // Restart blinking
        }
      }
    }
    break;
  }
}
