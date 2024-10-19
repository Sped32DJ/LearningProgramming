#include "rims.h"

enum states {
  INIT,
  IDLE,
  WATERING,
  NUTRIENT,
  LIGHTING_KONTROL,
  TEMPERATURE_KONTROL,
  MANUAL_OVERRIDE,
  STOP
} State;

// State machine function
void Tick() {
  // State Transitions
  switch (State) {
  case INIT:
    // Initialize all sensors and outputs to default values
    if (A & 0x40) {
      State = INIT;
    }
    State = IDLE;

  case IDLE:
    if (~A & 0x01)
      State = WATERING;
    if (~A & 0x02)
      State = NUTRIENT;
    if (~A & 0x04)
      State = LIGHTING_KONTROL;
    if (~A & 0x08)
      State = TEMPERATURE_KONTROL;
    if (A & 0x10)
      State = MANUAL_OVERRIDE;
    if (A & 0x20)
      State = STOP;
    if (A & 0x40)
      State = INIT;
    State = IDLE;
    break;

  case WATERING:
    if (A & 0x01) {
      B = B & ~0x01;
      State = IDLE;
    }
    State = WATERING;
    break;

  case NUTRIENT:
    if (A & 0x02) {
      B = B & ~0x02;
      State = IDLE;
    }
    State = NUTRIENT;
    break;

  case LIGHTING_KONTROL:
    if (A & 0x04) {
      B = B & ~0x04;
      State = IDLE;
    }
    State = LIGHTING_KONTROL;
    break;

  case TEMPERATURE_KONTROL:
    if (A & 0x08) {
      B = B & ~0x08;
      State = IDLE;
    }
    State = TEMPERATURE_KONTROL;
    break;

  case MANUAL_OVERRIDE:
    if (~A & 0x10) {
      State = IDLE;
    }
    State = MANUAL_OVERRIDE;
    break;

  case STOP:
    if (~A & 0x20) {
      State = IDLE;
    }
    State = STOP;
    break;

  default:
    State = INIT;
    break;
  }

  // State Actions
  switch (State) {
  case INIT:
    B = 0x00;
    break;

  case IDLE:
    break;

  case WATERING:
    // B0 = 1;
    B = B | 0x01;
    break;

  case NUTRIENT:
    // B1 = 1;
    B = B | 0x02;
    break;

  case LIGHTING_KONTROL:
    // B2 = 1;
    B = B | 0x04;
    break;

  case TEMPERATURE_KONTROL:
    // B3 = 1;
    B = B | 0x08;
    break;

  case MANUAL_OVERRIDE:
    break;

  case STOP:
    B = 0x00;
    break;

  case default:
    break;
  }
}

int main() {

  State = INIT;

  while (1) {
    Tick();
  }

  return 0;
}
