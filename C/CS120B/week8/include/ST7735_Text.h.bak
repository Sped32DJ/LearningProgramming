#ifndef ST7735_TEXT_H
#define ST7735_TEXT_H

#include "ST7735.h"
#include <avr/interrupt.h>

// Define font dimensions
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 7

// Placeholder font array (5x7 ASCII characters starting from ' ')
const uint8_t font[96][CHAR_WIDTH] = {
    // Add font data here. Each character is represented by 5 bytes (columns)
    // For example, for 'A' (ASCII 65), you'd have:
    // { 0x1F, 0x05, 0x05, 0x1F, 0x00 } // Simplified example
};

// Class for character handling
class ST7735_Text {
public:
  // Draw a single character
  void drawChar(int x, int y, char c, int color, int bgColor, uint8_t size) {
    if (c < 32 || c > 127)
      return; // Ensure valid ASCII range

    // Extract the bitmap for the character
    const uint8_t *charBitmap = font[c - 32];

    for (int col = 0; col < CHAR_WIDTH; col++) {
      uint8_t line = charBitmap[col];
      for (int row = 0; row < CHAR_HEIGHT; row++) {
        if (line & 0x01) {
          // Draw foreground pixel
          if (size == 1) {
            setPixel(x + col, y + row, color);
          } else {
            fillRect(x + col * size, y + row * size, size, size, color);
          }
        } else if (bgColor != color) {
          // Draw background pixel
          if (size == 1) {
            setPixel(x + col, y + row, bgColor);
          } else {
            fillRect(x + col * size, y + row * size, size, size, bgColor);
          }
        }
        line >>= 1;
      }
    }
  }

  // Draw a string starting at (x, y)
  void drawString(int x, int y, const char *str, int color, int bgColor,
                  uint8_t size) {
    while (*str) {
      drawChar(x, y, *str, color, bgColor, size);
      x += (CHAR_WIDTH + 1) * size; // Advance cursor for the next character
      str++;
    }
  }

private:
  // Helper to set a single pixel
  void setPixel(int x, int y, int color) {
    if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
      return;                  // Boundary check
    setAddrWindow(x, y, x, y); // Target single pixel
    Send_Data(color >> 8);     // Send high byte
    Send_Data(color & 0xFF);   // Send low byte
  }

  // Helper to fill a rectangle (used for scaled characters)
  void fillRect(int x, int y, int w, int h, int color) {
    setAddrWindow(x, y, x + w - 1, y + h - 1);
    for (int i = 0; i < w * h; i++) {
      Send_Data(color >> 8);   // High byte
      Send_Data(color & 0xFF); // Low byte
    }
  }
};

#endif // ST7735_TEXT_H
