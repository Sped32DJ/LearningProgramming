#include "main.cpp"

#ifndef IR_H
#define IR_H

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

#endif // IR_H
